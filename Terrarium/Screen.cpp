#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Game.hpp"

namespace terr {

	Screen::Screen()
	{
		if (!m_font.loadFromFile("arial.ttf"))
		{
			throw "Nie mo¿na wczytaæ czcionki arial.ttf!";
		};
	}

	Screen::~Screen() {}

	void Screen::draw(sf::RenderWindow& window)
	{
		sf::Text text;

		// select the font
		text.setFont(m_font);

		// set the string to display
		text.setString("Hello world oooo!");

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		// set the color
		text.setFillColor(sf::Color::Red);

		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		window.draw(text);
	}

}