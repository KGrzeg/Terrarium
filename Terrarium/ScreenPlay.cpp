#include "ScreenPlay.hpp"
#include "Utils.hpp"
#include <random>
#include <iostream>
#include <fstream>

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings& settings) :
		global(global), world(global, settings)
	{
		player = new Character(global, &world);
		player->setPosition(settings.player_x * TILE_WIDTH, settings.player_y * TILE_WIDTH);

		top_bar.setSize(sf::Vector2f(1280, 75));
		top_bar.setTexture(&global->assets.getTexture("ui/topbar"));

		score_label.setPosition(140, 20);
		score_label.setFont(global->assets.getFont("default"));
		score_label.setString("0");

		time_left = settings.initial_time;
		time_label.setPosition(460, 20);
		time_label.setFont(global->assets.getFont("default"));
		time_label.setString(std::to_string(static_cast<int>(time_left)));

		power_sprite = new SimpleAnimatedSprite(56, 18, global->assets.getTexture("ui/tools"));
		power_sprite->setPosition(248, 30);
		power_sprite->getSprite()->setOrigin(28, 9);
		power_sprite->getSprite()->setRotation(-45.0f);

		time_sprite = new SimpleAnimatedSprite(25, 47, global->assets.getTexture("ui/hourglass"));
		time_sprite->setPosition(428, 14);

		help_image.setSize(sf::Vector2f(1280, 720));
		help_image.setTexture(&global->assets.getTexture("help"));

		background_image.setSize({ settings.width * TILE_WIDTH * 1.f, WINDOW_HEIGHT });
		background_image.setTexture(&global->assets.getTexture(settings.background_texture_name));

		setup_drill(settings);
		setup_sheep(settings);

		this->settings = settings;
	}

	ScreenPlay::~ScreenPlay() {
		delete player, power_sprite, time_sprite, drill_tresholds;
	}

	void ScreenPlay::update(sf::Time time) {
		//skip heavy frames (ex. when world are generated)
		if (time.asSeconds() > 0.5f) return;
		if (display_help) return;

		update_elapsed_time += time;

		if (update_elapsed_time.asSeconds() >= update_fps) {
			player->update(update_elapsed_time);
			sheep->update(update_elapsed_time);
			time_sprite->update(update_elapsed_time);

			if (!is_lose && !is_win) {
				time_left -= update_elapsed_time.asSeconds();
				time_label.setString(std::to_string(static_cast<int>(time_left)));
			}

			update_elapsed_time = update_elapsed_time.Zero;
		}
		check_end_conditions();
	}

	void ScreenPlay::draw(sf::Time time)
	{
		global->window.clear();

		if (display_help) {
			global->window.draw(help_image);
		}
		else {
			global->window.draw(background_image);
			global->window.draw(world);
			global->window.draw(*player);
			global->window.draw(*sheep);

			draw_ui();
		}

		global->window.display();
		std::cout << sheep->getPosition().x - player->getPosition().x << ' ' << sheep->getPosition().y - player->getPosition().y << std::endl;
	}

	void ScreenPlay::draw_ui() {
		auto vue = global->window.getView();

		global->window.setView(global->window.getDefaultView());
		global->window.draw(top_bar);

		global->window.draw(score_label);
		global->window.draw(*power_sprite);
		global->window.draw(power_label);
		global->window.draw(*time_sprite);
		global->window.draw(time_label);

		global->window.setView(vue);
	}

	void ScreenPlay::setup_drill(WorldSettings& settings)
	{
		drill = new Drill(global, &world, player);
		drill->setPower(settings.default_power);

		power_label.setPosition(310, 20);
		power_label.setFont(global->assets.getFont("default"));
		power_label.setString(std::to_string(drill->getPower()));
	}

	void ScreenPlay::setup_sheep(WorldSettings& settings)
	{
		AnimationFrameDef* frames = new AnimationFrameDef[2]{ {54, 58, 13, 9}, {67, 58, 13, 9} };
		AnimationDef* anims = new AnimationDef[1]{ { 0, 1 } };
		sheep = new AnimatedSprite(anims, frames, true);
		sheep->setTexture(global->assets.getTexture("game/map1"));

		int random_x = (rand() % (settings.width - SHEEP_HOLE_MARGIN * 2)) + SHEEP_HOLE_MARGIN;
		sheep->setPosition(random_x * TILE_WIDTH, (settings.height - 1) * TILE_HEIGHT);

		world.makeSheepHole(random_x);
	}

	void ScreenPlay::check_end_conditions()
	{
		if (Utils::distance(player->getPosition(), sheep->getPosition()) < SHEEP_WIN_DISTANCE) {
			is_win = true;
			player->win();
		}

		if (time_left <= 0) {
			is_lose = true;
			player->lose();
		}
	}

	void ScreenPlay::upgrade_tool()
	{
		int cur_power = drill->getPower();
		if (cur_power >= TOOLS_MAX_UPGRADE)
			return;

		if (score > drill_tresholds[cur_power]) {
			power_sprite->setAnimation(cur_power);
			drill->setPower(++cur_power);
			power_label.setString(std::to_string(cur_power));
		}
	}

	void ScreenPlay::save()
	{
		std::fstream writeFile;
		writeFile.open(settings.name + ".sav", std::fstream::out);

		if (!writeFile.good()) {
			writeFile.close();
			return;
		}

		writeFile << world;
		writeFile << settings;
		writeFile << *player;

		writeFile << sheep->getPosition().x << ' ';
		writeFile << sheep->getPosition().y << ' ';

		writeFile << score << ' ';
		writeFile << time_left << std::endl;

		writeFile.close();
	}

	void ScreenPlay::load()
	{
		std::fstream readFile;
		readFile.open(settings.name + ".sav", std::fstream::in);

		if (!readFile.good()) {
			readFile.close();
			return;
		}

		readFile >> world;
		readFile >> settings;
		readFile >> *player;

		float x, y;
		readFile >> x >> y;
		sheep->setPosition(x, y);

		readFile >> score;
		readFile >> time_left;

		upgrade_tool();
		time_label.setString(std::to_string(static_cast<int>(time_left)));
		score_label.setString(std::to_string(score));

		readFile.close();
	}

	void ScreenPlay::handle_input() {
		sf::Event event;
		while (global->window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				global->window.close();

			if (display_help) {
				if (event.type == sf::Event::KeyPressed) {
					display_help = false;
				}
			}
			else {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						global->navigator.goBack();
					}
					if (event.key.code == sf::Keyboard::F1) {
						global->window.setView(global->window.getDefaultView());
						display_help = true;
					}
					if (event.key.code == sf::Keyboard::F5) {
						save();
					}
					if (event.key.code == sf::Keyboard::F6) {
						load();
					}
					if (event.key.code == sf::Keyboard::F11 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						drill->setPower(std::max((drill->getPower() + 1) % 4, 1));
						power_sprite->setAnimation(drill->getPower() - 1);
						power_label.setString(std::to_string(drill->getPower()));
					}
				}

				if (!is_lose && !is_win) {
					player->handle_event(event);
					int score = drill->feedEvent(event);

					if (score) {
						player->playMineAnimation();
						addScore(score);
					}
				}
			}

		}
	}

	void ScreenPlay::addScore(int scr) {
		score += scr;
		time_left += scr * SCORE_TO_TIME_RATIO;
		score_label.setString(std::to_string(score));
		upgrade_tool();
	}
	void ScreenPlay::pause()
	{
		global->window.setView(global->window.getDefaultView());
	}
}