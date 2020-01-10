#include "ScreenPlay.hpp"

namespace terr {
	ScreenPlay::ScreenPlay(GlobalReference global, WorldSettings settings) :
		global(global), world(settings)
	{
		animeddd = new AnimatedSprite(80, 80, global->assets.getTexture("game/character2"));
		animeddd->setPosition(100, 100);
		animeddd->setAnimation(3);
	}

	void ScreenPlay::update(sf::Time time) {
		animeddd->update(time);
	}

	void ScreenPlay::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(world);
		global->window.draw(*animeddd);
		global->window.display();
	}
}