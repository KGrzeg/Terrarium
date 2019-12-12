#pragma once
#include "Screen.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "UIElement.hpp"
#include "Label.hpp"
#include "UIGrid.hpp"

namespace terr {
	typedef std::unique_ptr<UIElement> UIElementReference;
	
	class ScreenNewGame : public Screen
	{
	public:
		ScreenNewGame(GlobalReference global);
		void draw(sf::Time time);

		void update(sf::Time time) override;
		void handle_input() override;


	private:
		GlobalReference global;
		
		/*Label title;
		Label world_name_lbl;
		Label resources_lbl;

		Button btn_start;
		Button btn_back;*/

		UIGrid grid;

		sf::RectangleShape m_background_rectangle;
	};
}
