#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"
#include "Button.hpp"

namespace terr {
	class ScreenMainMenu :
		public ScreenMenu
	{
	public:
		ScreenMainMenu(sf::String name) : ScreenMenu(name) {}
		~ScreenMainMenu() = default;

		void setup(sf::Font &fnt, sf::RenderWindow& window)
		{
			ScreenMenu::setup(fnt, window);

			AddElement(new Button(m_font, L"Zacznij grê"));
			AddElement(new Button(m_font, L"Wczytaj grê"));
			AddElement(new Button(m_font, L"Pomoc"));
			AddElement(new Button(m_font, L"Ustawienia"));
			AddElement(new Button(m_font, L"O autorze"));
			AddElement(new Button(m_font, L"Wyjscie"));
		}
	};

}
