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
	}

	void ScreenPlay::update(sf::Time time) {
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
		global->window.draw(world);
		global->window.draw(*player);

		draw_ui();

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

			player->handle_event(event);
			int score = pickaxe->feedEvent(event);

			if (score) {
				player->playMineAnimation();
				addScore(score);
			}

			if (event.type == sf::Event::Closed)
				global->window.close();
		}
	}

	void ScreenPlay::addScore(int scr) {
		score += scr;
		score_label.setString(std::to_string(score));
	}
}