#include "ScreenPlay.hpp"

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings settings) :
		global(global), world(settings)
	{
		player = new Character(global);
		player->setPosition(100, 100);
	}

	void ScreenPlay::update(sf::Time time) {
		player->update(time);
	}

	void ScreenPlay::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(world);
		global->window.draw(*player);
		global->window.display();
	}
}