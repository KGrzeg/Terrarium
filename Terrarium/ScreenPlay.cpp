#include "ScreenPlay.hpp"

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings settings) :
		global(global), world(global, settings)
	{
		player = new Character(global, &world);
		player->setPosition(100, 20);
		fps_meter.setFont(global->assets.getFont("default"));
		fps_meter.setPosition(15, 15);
		fps_meter.setFillColor(sf::Color::White);
	}

	void ScreenPlay::update(sf::Time time) {
		update_elapsed_time += time;
		fps_meter.setString("fps: " + std::to_string(1 / time.asSeconds()));

		if (update_elapsed_time.asSeconds() >= update_fps) {
			player->update(time);
			update_elapsed_time -= sf::seconds(update_fps);
		}
	}

	void ScreenPlay::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(world);
		global->window.draw(*player);

		global->window.draw(fps_meter);
		global->window.display();
	}

}