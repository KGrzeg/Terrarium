#include "Game.hpp"

namespace terr {
	Game::Game() : m_window(sf::VideoMode(this->window_width, this->window_height),
		this->name + " v" + this->version,
		sf::Style::Titlebar | sf::Style::Close),
		screen_play(50, 50)
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

		sf::Texture menu_background_text;
		if (!menu_background_text.loadFromFile("images/menu_background.jpg"))
		{
			throw L"Nie mo¿na wczytaæ obrazu images/menu_background.jpg!";
		}

		m_menu_main.setup(this, menu_background_text);
		m_menu_main.addPosition(L"Nowa Gra");
		m_menu_main.addPosition(L"Wczytaj Grê");
		m_menu_main.addPosition(L"Autor");
		m_menu_main.addPosition(L"Pomoc");
		m_menu_main.addPosition(L"Wyjœcie");

		m_menu_load.setup(this, menu_background_text);
		m_menu_load.addPosition(L"Slot 1");
		m_menu_load.addPosition(L"Slot 2");
		m_menu_load.addPosition(L"Slot 3");
		m_menu_load.addPosition(L"Wróæ");

		m_menu_new_game.setup(this);

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

		handleMenus(event);
	}

	void Game::handleMenus(sf::Event& event)
	{
		if (m_current_screen_type == newgame)
		{
			handleNewgameMenu(event);
			return;
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			ScreenMenu *menu = dynamic_cast<ScreenMenu *>(m_current_screen);
			if (menu && menu->getSelectedPosition() != -1)
			{

				switch (m_current_screen_type)
				{
				case main:
				{
					handleMainMenu();
					break;
				}
				case loadgame:
				{
					handleLoadgameMenu();
					break;
				}
				}
			}
		}
	}



	void Game::handleMainMenu()
	{
		switch (m_menu_main.getSelectedPosition())
		{
		case 0: {
			//setScreen(newgame);
			setScreen(game);
			break;
		}
		case 1: {
			setScreen(loadgame);
			break;
		}
		case 4: {
			quit();
			break;
		}
		}
	}

	void Game::handleNewgameMenu(sf::Event &event)
	{
		m_menu_new_game.handleEvent(event);
	}


	void Game::handleLoadgameMenu()
	{
		switch (m_menu_load.getSelectedPosition())
		{
		case 3: {
			setScreen(main);
			break;
		}
		}
	}

	void Game::draw()
	{
		m_window.clear(sf::Color::Black);

		m_current_screen->draw(m_window);

		m_window.display();
	}

	void Game::setScreen(game_screen_type screen)
	{
		m_current_screen_type = screen;
		switch (screen)
		{
		case game:
		{
			m_current_screen = &screen_play;
			break;
		}
		case main:
		{
			m_current_screen = &m_menu_main;
			break;
		}
		case newgame:
		{
			m_current_screen = &m_menu_new_game;
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