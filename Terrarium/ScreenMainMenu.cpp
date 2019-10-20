#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenMainMenu.hpp"

namespace terr {

	ScreenMainMenu::ScreenMainMenu()
	{
		m_texts.push_back(sf::Text(L"Zacznij grê", m_font, m_buttons_size));
		m_texts.push_back(sf::Text(L"Wczytaj grê", m_font, m_buttons_size));
		m_texts.push_back(sf::Text(L"Pomoc", m_font, m_buttons_size));
		m_texts.push_back(sf::Text(L"Ustawienia", m_font, m_buttons_size));
		m_texts.push_back(sf::Text(L"O Autorze", m_font, m_buttons_size));
		m_texts.push_back(sf::Text(L"Wyjœcie", m_font, m_buttons_size));
	}
	ScreenMainMenu::~ScreenMainMenu() {}

	void ScreenMainMenu::draw(sf::RenderWindow& window)
	{
		unsigned int middle_x = window.getSize().x / 2;

		for (std::vector<sf::Text>::size_type i = 0; i < m_texts.size(); ++i)
		{
			float x = middle_x - m_texts[i].getLocalBounds().width / 2;
			float y = m_first_button_offset + i * (m_buttons_margin + m_buttons_size);
			m_texts[i].setPosition(x, y);

			window.draw(m_texts[i]);
		}
	}


}