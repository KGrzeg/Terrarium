#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"

namespace terr {
	class ScreenMainMenu :
		public ScreenMenu
	{
	public:
		ScreenMainMenu(sf::String name) : ScreenMenu(name) {}
		~ScreenMainMenu() = default;

		void setup(sf::Font &fnt)
		{
			ScreenMenu::setup(fnt);

			m_texts.emplace_back(L"Zacznij grê", m_font, m_buttons_size);
			m_texts.emplace_back(L"Wczytaj grê", m_font, m_buttons_size);
			m_texts.emplace_back(L"Pomoc", m_font, m_buttons_size);
			m_texts.emplace_back(L"Ustawienia", m_font, m_buttons_size);
			m_texts.emplace_back(L"O Autorze", m_font, m_buttons_size);
			m_texts.emplace_back(L"Wyjœcie", m_font, m_buttons_size);
		}
	};

}
