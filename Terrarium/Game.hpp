#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"

namespace terr {
	enum game_menu
	{
		main,
		author,
		loadgame,
		newgame,
		help
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
		void handleEvent(sf::Event &event);
		void draw();

		void setScreen(game_menu screen);
		sf::Font getDefaultFont() const;
		sf::RenderWindow* getWindowPtr();

	private:
		sf::RenderWindow m_window;
		sf::Font m_default_font;

		ScreenMenu m_menu_main;
		ScreenMenu m_menu_load;
		Screen* m_current_screen;
	};
}
