#pragma once
#include "Screen.hpp"

namespace terr {
	class ScreenMenu : public Screen
	{
	public:
		void draw(sf::RenderWindow& window);
		void update() {}

		void addPosition(sf::String msg);
		
	private:
		std::vector<sf::Text> m_positions;
		const int m_first_button_offset = 130;
		const int m_menu_font_size = 28;
		const sf::Color m_default_color = sf::Color::White;
		const sf::Color m_hover_color = sf::Color::Yellow;
	};
}
