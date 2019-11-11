#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"

namespace terr {
	enum Game_Sreen
	{
		MainMenu,
		Author
	};

	class Game
	{
	public:
		const std::string name = "Terrarium";
		const std::string version = "0.1";
		const int window_width = 1280;
		const int window_height = 720;

		Game();
		~Game() = default;

		void setup();
		void start();
		void quit();

		void update();
		void draw();

		void setScreen(Game_Sreen screen);
		sf::Font getDefaultFont() const;
		sf::RenderWindow* getWindowPtr();

	private:
		sf::RenderWindow m_window;
		sf::Font m_default_font;

		Game_Sreen m_game_screen = MainMenu;
		ScreenMenu m_main_menu;
		ScreenMenu* m_current_screen;

	};
}
