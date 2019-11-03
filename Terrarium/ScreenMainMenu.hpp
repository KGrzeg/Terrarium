#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"
#include "Game.hpp"

namespace terr {
	class Game;
	class ScreenMenu;
	
	class ScreenMainMenu :
		public ScreenMenu
	{
	public:
		ScreenMainMenu(sf::String name) : ScreenMenu(name) {}

		void setup(Game* game);
		void draw(sf::RenderWindow&);
		void update();
	};

}
