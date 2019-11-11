#pragma once
#include "Screen.hpp"

namespace terr {
	class ScreenMenu : public Screen
	{
	public:
		void draw(sf::RenderWindow& window) override;
		void update(Game *) override;
		void setup(Game *, sf::Texture&);

		void addPosition(sf::String msg);
		int getSelectedPosition();
		
	private:
		std::vector<sf::Text> m_positions;
		const int m_menu_font_size = 50;

		int m_selected = 0;
		bool m_hover_on_something = false;
		
		const sf::Color m_default_color = sf::Color::White;
		const sf::Color m_hover_color = sf::Color::Cyan;

		sf::Texture m_background_texture;
		sf::RectangleShape m_background_shape;
	};
}
