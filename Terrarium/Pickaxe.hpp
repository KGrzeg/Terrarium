#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "World.hpp"

namespace terr {

	class Pickaxe
	{
	public:
		Pickaxe(GlobalReference global, World* world);
		//void update(sf::Time& time);
		int feedEvent(sf::Event& event);

		int getPower() const { return power; }
		void setPower(int pow) { power = pow; }

	private:
		GlobalReference global;
		World* world;
		int power = 1;
	};

}