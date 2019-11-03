#pragma once
#include "ScreenMenu.hpp"
#include "Game.hpp"

namespace  terr
{
	class Game;
	class ScreenMenu;
	class ScreenAuthor : public ScreenMenu
	{
	public:
		ScreenAuthor(sf::String name) : ScreenMenu(name) {}

		void setup(Game* game);
		void draw(sf::RenderWindow&);
		void update();
	};
}
