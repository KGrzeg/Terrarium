#pragma once
#include "ScreenMenu.hpp"

namespace  terr
{
	class ScreenAuthor : public ScreenMenu
	{
	public:
		ScreenAuthor(sf::String name) : ScreenMenu(name) {}
		
		void setup(sf::Font &fnt)
		{
			ScreenMenu::setup(fnt);

			m_texts.emplace_back(L"Autor Gry", m_font, m_buttons_size);
			m_texts.emplace_back(L"Grzegorz Kupczyk", m_font, m_buttons_size);
			m_texts.emplace_back(L" ", m_font, m_buttons_size);
			m_texts.emplace_back(L"Wróæ", m_font, m_buttons_size);
			m_texts.emplace_back(L"Wyjœcie", m_font, m_buttons_size);
		}
	};
}
