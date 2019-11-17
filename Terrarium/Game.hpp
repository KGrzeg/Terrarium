#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ScreenMenu.hpp"
#include "ScreenNewGame.hpp"

namespace terr {
	enum game_screen_type
	{
		main,
		author,
		loadgame,
		newgame,
		help,
		game
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

		void setScreen(game_screen_type screen);
		sf::Font getDefaultFont() const;
		sf::RenderWindow* getWindowPtr();

	private:
		void handleMenus(sf::Event& event);
		void handleMainMenu();
		void handleNewgameMenu(sf::Event &event);
		void handleLoadgameMenu();

		sf::RenderWindow m_window;
		sf::Font m_default_font;

		ScreenMenu m_menu_main;
		ScreenMenu m_menu_load;
		ScreenNewGame m_menu_new_game;
		Screen* m_current_screen;
		game_screen_type m_current_screen_type;
	};
}
