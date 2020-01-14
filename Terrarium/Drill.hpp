#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "World.hpp"
#include "Character.hpp"

namespace terr {

	class Drill
	{
	public:
		Drill(GlobalReference global, World* world, Character* player);
		//void update(sf::Time& time);
		int feedEvent(sf::Event& event);

		int getPower() const { return power; }
		void setPower(int pow) { power = pow; }

	private:
		float range = 120;

		GlobalReference global;
		World* world;
		Character* player;
		int power = 1;
	};

}