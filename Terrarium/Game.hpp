#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Screen.hpp"
#include "ScreenMainMenu.hpp"

namespace terr {

	class Game
	{
	public:
		const std::string name = "Terrarium";
		const std::string version = "0.1";
		const int window_width = 800;
		const int window_height = 600;

		Game()
			:m_window(sf::VideoMode(this->window_width, this->window_height),
				this->name + " v" + this->version,
				sf::Style::Titlebar | sf::Style::Close),
			m_main_screen(L"Menu G³ówne")
		{
			m_window.setVerticalSyncEnabled(true);
			m_current_screen = &m_main_screen;

			setup();
		}
		~Game() = default;

		void setup()
		{
			sf::Font default_font;
			if (!default_font.loadFromFile("arial.ttf"))
			{
				throw "Nie mo¿na wczytaæ czcionki arial.ttf!";
			};

			m_main_screen.setup(default_font);

			m_current_screen = &m_main_screen;
		}


		void start()
		{
			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						this->quit();
				}

				this->draw();
			}
		}

		void update() {}

		void draw()
		{
			m_window.clear(sf::Color::Black);

			m_main_screen.draw(m_window);

			m_window.display();
		}

		void quit()
		{
			m_window.close();
		}
	private:
		sf::RenderWindow m_window;

		ScreenMainMenu m_main_screen;
		Screen *m_current_screen;

	};
}
