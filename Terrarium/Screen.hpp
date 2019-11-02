#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace terr {
	class Screen
	{
	public:
		~Screen() = default;
		Screen(sf::String name);

		virtual void setup(Game*) = 0;
		virtual void draw(sf::RenderWindow&) = 0;
		virtual void update() = 0;

	protected:
		std::string m_name;
	};

}