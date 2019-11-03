#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace terr {
	class Game;
	class Screen
	{
	public:
		Screen(sf::String name);

		void setup(Game*) {};
		void draw(sf::RenderWindow&) {};
		void update() {};

	protected:
		std::string m_name;
	};

}