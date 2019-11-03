#include "Game.hpp"

namespace terr {
	Game::Game() : m_window(sf::VideoMode(this->window_width, this->window_height),
		this->name + " v" + this->version,
		sf::Style::Titlebar | sf::Style::Close)/*,
		m_main_screen(L"Menu G³ówne"),
		m_author_screen(L"Autor")*/
	{
		m_window.setVerticalSyncEnabled(true);

		setup();
	}

	void Game::setup()
	{
		if (!m_default_font.loadFromFile("arial.ttf"))
		{
			throw L"Nie mo¿na wczytaæ czcionki arial.ttf!";
		};

		//m_main_screen.setup(this);
		//m_author_screen.setup(this);

		//m_current_screen = &m_main_screen;
	}

	void Game::start()
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

	void Game::update()
	{
	}

	void Game::draw()
	{
		m_window.clear(sf::Color::Black);

		//m_current_screen->draw(m_window);

		m_window.display();
	}

	void Game::setScreen(Game_Sreen screen)
	{
		switch (m_gameScreen)
		{
		case MainMenu:
		{
			//m_current_screen = &m_main_screen;
			break;
		}
		case Author:
		{
			//m_current_screen = &m_author_screen;
			break;
		}
		}

		m_gameScreen = screen;
	}

	sf::Font Game::getDefaultFont() const { return m_default_font; }
	sf::RenderWindow* Game::getWindowPtr() { return &m_window; }

	void Game::quit()
	{
		m_window.close();
	}
}