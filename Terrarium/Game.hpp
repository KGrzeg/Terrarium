#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ScreenMainMenu.hpp"
#include "ScreenAuthor.hpp"

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
		const int window_width = 800;
		const int window_height = 600;

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

		ScreenMainMenu m_main_screen;
		ScreenAuthor m_author_screen;
		Screen *m_current_screen;
		Game_Sreen m_gameScreen = MainMenu;

	};
}
