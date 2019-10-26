#pragma once
#include <vector>
#include "Screen.hpp"

namespace terr {
	class ScreenMenu :
		public terr::Screen
	{
	public:
		ScreenMenu(sf::String name) :Screen(name) {	}
		~ScreenMenu() = default;

		void setup(sf::Font& fnt)
		{
			Screen::setup(fnt);
		}
		void draw(sf::RenderWindow& window)
		{
			const unsigned int middle_x = window.getSize().x / 2;

			for (std::vector<sf::Text>::size_type i = 0; i < m_texts.size(); ++i)
			{
				float x = middle_x - m_texts[i].getLocalBounds().width / 2;
				float y = m_first_button_offset + i * (m_buttons_margin + m_buttons_size);
				m_texts[i].setPosition(x, y);

				window.draw(m_texts[i]);
			}
		}

	protected:
		std::vector<sf::Text> m_texts;
		const int m_buttons_margin = 10;
		const int m_buttons_size = 30;
		const int m_first_button_offset = 130;
	};
}