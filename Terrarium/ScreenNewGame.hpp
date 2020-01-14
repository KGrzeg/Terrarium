#pragma once
#include "Screen.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "UIElement.hpp"
#include "Label.hpp"
#include "UIGrid.hpp"
#include "World.hpp"

namespace terr {
	typedef std::unique_ptr<UIElement> UIElementReference;
	
	class ScreenNewGame : public Screen
	{
	public:
		ScreenNewGame(GlobalReference global);
		~ScreenNewGame();
		void draw(sf::Time time);

		void update(sf::Time time) override;
		void handle_input() override;


	private:
		void setup_maps();
		void select_map(int id);

		int selected_map = 0;
		WorldSettings map_definitions[DEFINED_MAPS];
		GlobalReference global;		
		UIGrid grid;
		Label *lbl_name, *lbl_difficulty, *lbl_dimension;
		sf::RectangleShape m_background_rectangle;
	};
}
