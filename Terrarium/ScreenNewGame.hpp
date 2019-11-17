#pragma once
#include "Screen.hpp"

namespace terr {
	class ScreenNewGame : public Screen
	{
	public:
		void draw(sf::RenderWindow& window) override;
		void update(Game *) override;
		void setup(Game *) override;
		void handleEvent(sf::Event &e);
		
	private:
		//lbl- label
		//ctrl - controll
		sf::Text m_lbl_title;
		sf::Text m_lbl_world_name;
		sf::Text m_lbl_resources_level;
		
		sf::Text m_ctrl_world_name;
		sf::Text m_ctrl_resources_level;

		sf::Text m_btn_back;
		sf::Text m_btn_start;
		
		sf::Texture m_background_tex;
		sf::RectangleShape m_background_rectangle;
		int m_active_control = -1;
	};
}