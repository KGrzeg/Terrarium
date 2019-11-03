#pragma once
#include <vector>
#include "UIElement.hpp"
#include "Game.hpp"
#include "Screen.hpp"

namespace terr {
	class Game;
	class Screen;
	class ScreenMenu : public Screen
	{
	public:
		ScreenMenu(sf::String name);
		~ScreenMenu();

		void setup(Game* game);
		void draw(sf::RenderWindow& window);
		void update() {}
		
		UIElement* AddElement(UIElement* elem);

	protected:
		std::vector<UIElement*> m_elements;
		const int m_first_button_offset = 130;
		int m_middle;
	};
}
