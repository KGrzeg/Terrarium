#include "Game.hpp"

namespace terr {
	Game::Game() : m_window(sf::VideoMode(this->window_width, this->window_height),
		this->name + " v" + this->version,
		sf::Style::Titlebar | sf::Style::Close)
	{
		m_window.setVerticalSyncEnabled(true);

		setup();
	}

	void Game::setup()
	{
		if (!m_default_font.loadFromFile("arial.ttf"))
		{
			throw L"Nie mo¿na wczytaæ czcionki arial.ttf!";
		}
		
		m_menu_main.setup(this);
		m_menu_main.addPosition(L"Nowa Gra");
		m_menu_main.addPosition(L"Wczytaj Grê");
		m_menu_main.addPosition(L"Autor");
		m_menu_main.addPosition(L"Pomoc");
		m_menu_main.addPosition(L"Wyjœcie");

		m_menu_load.setup(this);
		m_menu_load.addPosition(L"Slot 1");
		m_menu_load.addPosition(L"Slot 2");
		m_menu_load.addPosition(L"Slot 3");
		m_menu_load.addPosition(L"Wróæ");

		m_current_screen = &m_menu_main;
	}

	void Game::start()
	{
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				handleEvent(event);
			}

			this->update();
			this->draw();
		}
	}

	void Game::update()
	{
		m_current_screen->update(this);
	}

	void Game::handleEvent(sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
			this->quit();
	}

	void Game::draw()
	{
		m_window.clear(sf::Color::Black);

		m_current_screen->draw(m_window);

		m_window.display();
	}

	void Game::setScreen(game_menu screen)
	{
		switch (screen)
		{
		case main:
		{
			m_current_screen = &m_menu_main;
			break;
		}
		case loadgame:
		{
			m_current_screen = &m_menu_load;
			break;
		}
		}

	}

	sf::Font Game::getDefaultFont() const { return m_default_font; }
	sf::RenderWindow* Game::getWindowPtr() { return &m_window; }

	void Game::quit()
	{
		m_window.close();
	}
}