#pragma once
#include "Screen.hpp"

namespace terr {
	class ScreenMenu : public Screen
	{
	public:
		void draw(sf::RenderWindow& window) override;
		void update(Game *) override;

		void addPosition(sf::String msg);
		
	private:
		std::vector<sf::Text> m_positions;
		const int m_menu_font_size = 50;
		const sf::Color m_default_color = sf::Color::White;
		const sf::Color m_hover_color = sf::Color::Yellow;
	};
}
