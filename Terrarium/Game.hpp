#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Screen.hpp"

namespace terr {

	class Game
	{
	public:
		const std::string name = "Terrarium";
		const std::string version = "0.1";
		const int window_width = 800;
		const int window_height = 600;

		Game();
		~Game();

		void start();

		sf::Font getDefaultFont() const;
		sf::RenderWindow& getWindow();

	private:
		sf::RenderWindow m_window;
		sf::Font m_default_font;
		std::unique_ptr<Screen> m_start_screen;
		Screen *m_current_screen;

		void update();
		void draw();
		void quit();
	};
}
