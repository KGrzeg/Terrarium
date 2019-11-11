#pragma once
#include <SFML/Graphics.hpp>

namespace terr {

	class Game;

	class Screen
	{
	public:
		Screen() {};

		void setup(Game *game);
		void draw(sf::RenderWindow&) {};
		void update() {};

	protected:
		sf::Font m_font;
		sf::Vector2u m_window_size;
	};

}