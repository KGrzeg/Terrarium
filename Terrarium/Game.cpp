#include "Game.hpp"
#include "ScreenMainMenu.hpp"

namespace terr {
	Game::Game()
	{
		global->window.create(sf::VideoMode(window_width, window_height),
			name + " v" + version,
			sf::Style::Titlebar | sf::Style::Close);
		//screen_play(180, 90)
		global->window.setVerticalSyncEnabled(true);

		global->assets.addFont("default", "arial.ttf");
		global->assets.addTexture("menu/background", "images/menu_background.jpg");

		global->navigator.setScreen(ScreenReference(new ScreenMainMenu(global)), false);
	}

	void Game::start()
	{
		while (global->window.isOpen())
		{
			elapsed_time = global_clock.restart();

			global->navigator.getScreen()->handle_input();
			global->navigator.getScreen()->update(elapsed_time);
			global->navigator.getScreen()->draw(elapsed_time);
		}
	}
	/*void Game::handleMenus(sf::Event& event)
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
	}*/



	//void Game::handleMainMenu()
	//{
	//	switch (m_menu_main.getSelectedPosition())
	//	{
	//	case 0: {
	//		//setScreen(newgame);
	//		setScreen(game);
	//		break;
	//	}
	//	case 1: {
	//		setScreen(loadgame);
	//		break;
	//	}
	//	case 4: {
	//		quit();
	//		break;
	//	}
	//	}
	//}

	//void Game::handleNewgameMenu(sf::Event &event)
	//{
	//	m_menu_new_game.handleEvent(event);
	//}


	//void Game::handleLoadgameMenu()
	//{
	//	switch (m_menu_load.getSelectedPosition())
	//	{
	//	case 3: {
	//		setScreen(main);
	//		break;
	//	}
	//	}
	//}
}
