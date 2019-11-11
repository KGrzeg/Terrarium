#pragma once
#include <SFML/Graphics.hpp>

namespace terr {

	class Game;

	class Screen
	{
	public:
		Screen() {};

		virtual void setup(Game *game);
		virtual void draw(sf::RenderWindow&) {};
		virtual void update(Game *game) {};

	protected:
		sf::Font m_font;
		sf::Vector2u m_window_size;
	};

}