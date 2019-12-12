#include "ScreenPlay.hpp"

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings settings) :
		global(global), world(settings)
	{
	}


	void ScreenPlay::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(world);
		global->window.display();
	}
}