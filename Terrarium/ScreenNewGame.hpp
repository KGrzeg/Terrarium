#pragma once
#include "Screen.hpp"
#include "Game.hpp"

namespace terr {
	class Game;

	class ScreenNewGame : public Screen
	{
	public:
		ScreenNewGame(GlobalReference global);
		void draw(sf::Time time);

		void setup() {};
		void handle_input() {};
		void update(sf::Time time) {};
		
		
	private:
		GlobalReference global;
		sf::Text m_lbl_title;
		sf::Text m_lbl_world_name;
		sf::Text m_lbl_resources_level;
		
		sf::Text m_ctrl_world_name;
		sf::Text m_ctrl_resources_level;

		sf::Text m_btn_back;
		sf::Text m_btn_start;
		
		sf::RectangleShape m_background_rectangle;
	};
}