#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Game.hpp"

namespace terr {

	Screen::Screen() { }
	Screen::Screen(sf::Font& font)
	{
		m_font = font;
		m_background_color = sf::Color::Black;
	}

	Screen::~Screen() {}


	void Screen::draw(sf::RenderWindow& window)
	{
		sf::Text text;

		// select the font
		text.setFont(m_font);

		// set the string to display
		text.setString("Hello world");

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		// set the color
		text.setFillColor(sf::Color::Red);

		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		window.clear(m_background_color);

		window.draw(text);
	}

}