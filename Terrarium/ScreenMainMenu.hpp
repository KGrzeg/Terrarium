#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Screen.hpp"

namespace terr {

	class ScreenMainMenu:
		public terr::Screen
	{
	public:
		ScreenMainMenu();
		~ScreenMainMenu();

		void draw(sf::RenderWindow&);

	private:
		std::vector<sf::Text> m_texts;
		const int m_buttons_margin = 10;
		const int m_buttons_size = 30;
		const int m_first_button_offset = 100;
	};

}