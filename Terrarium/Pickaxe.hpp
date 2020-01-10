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
		void feedEvent(sf::Event& event);

	private:
		GlobalReference global;
		World* world;
		int power = 1;
	};

}