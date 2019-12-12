#pragma once
#include "Screen.hpp"
#include "Game.hpp"

namespace terr {
	class ScreenMenu : public Screen
	{
	public:
		ScreenMenu(GlobalReference global);

		void handle_input();
		void draw(sf::Time time);
		void update(sf::Time time);

		void addPosition(sf::String msg);

	protected:
		GlobalReference global;
		virtual void clicked_option(int id) {};
		
	private:		
		std::vector<sf::Text> m_positions;
		const int m_menu_font_size = 50;

		int m_hover_above = 0;
		
		const sf::Color m_default_color = sf::Color::White;
		const sf::Color m_hover_color = sf::Color::Cyan;

		sf::RectangleShape m_background_shape;
	};
}
