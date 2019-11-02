#pragma once
#include "ScreenMenu.hpp"

namespace  terr
{
	class ScreenAuthor : public ScreenMenu
	{
	public:
		ScreenAuthor(sf::String name) : ScreenMenu(name) {}
		
		void setup(sf::Font &fnt, sf::RenderWindow& window)
		{
			ScreenMenu::setup(fnt, window);

			AddElement(new UIElement(m_font, L"Autor Gry"));
			AddElement(new UIElement(m_font, L"Grzegorz Kupczyk"));
			AddElement(new Button(m_font, L"Wróæ"));
			AddElement(new Button(m_font, L"Wyjscie"));
		}
	};
}
