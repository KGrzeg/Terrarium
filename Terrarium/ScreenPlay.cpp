#include "ScreenPlay.hpp"

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings settings) :
		global(global), world(global, settings)
	{
		player = new Character(global, &world);
		player->setPosition(settings.player_x, settings.player_y);

		pickaxe = new Pickaxe(global, &world, player);

		top_bar.setSize(sf::Vector2f(1280, 75));
		top_bar.setTexture(&global->assets.getTexture("ui/topbar"));

		power_label.setPosition(310, 20);
		power_label.setFont(global->assets.getFont("default"));
		power_label.setString(std::to_string(pickaxe->getPower()));

		score_label.setPosition(140, 20);
		score_label.setFont(global->assets.getFont("default"));
		score_label.setString("0");

		power_sprite = new SimpleAnimatedSprite(64, 64, global->assets.getTexture("ui/tools"));
		power_sprite->setPosition(220, 6);

		help_image.setSize(sf::Vector2f(1280, 720));
		help_image.setTexture(&global->assets.getTexture("help"));

		background_image.setSize({ settings.width * TILE_WIDTH * 1.f, WINDOW_HEIGHT });
		background_image.setTexture(&global->assets.getTexture(settings.background_texture_name));
	}

	ScreenPlay::~ScreenPlay() {
		delete player;
	}


	void ScreenPlay::update(sf::Time time) {
		if (display_help) return;

		update_elapsed_time += time;

		if (update_elapsed_time.asSeconds() >= update_fps) {
			player->update(time);
			update_elapsed_time -= sf::seconds(update_fps);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			pickaxe->setPower(std::max((pickaxe->getPower() + 1) % 4, 1));
			power_sprite->setAnimation(pickaxe->getPower() - 1);
			power_label.setString(std::to_string(pickaxe->getPower()));
		}
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

			draw_ui();
		}

		global->window.display();

	}

	void ScreenPlay::draw_ui() {
		auto vue = global->window.getView();

		global->window.setView(global->window.getDefaultView());
		global->window.draw(top_bar);

		global->window.draw(score_label);
		global->window.draw(*power_sprite);
		global->window.draw(power_label);

		global->window.setView(vue);
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
				}

				player->handle_event(event);
				int score = pickaxe->feedEvent(event);

				if (score) {
					player->playMineAnimation();
					addScore(score);
				}
			}

		}
	}

	void ScreenPlay::addScore(int scr) {
		score += scr;
		score_label.setString(std::to_string(score));
	}
	void ScreenPlay::pause()
	{
		global->window.setView(global->window.getDefaultView());
	}
}