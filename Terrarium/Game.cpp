#include "Game.hpp"
#include "ScreenMainMenu.hpp"

namespace terr {
	Game::Game()
	{
		global->window.create(sf::VideoMode(window_width, window_height),
			name + " v" + version,
			sf::Style::None);
		//screen_play(180, 90)
		global->window.setVerticalSyncEnabled(true);

		global->assets.addFont("default", "arial.ttf");
		global->assets.addTexture("menu/background", "images/menu_background.jpg");

		global->navigator.pushScreen(ScreenReference(new ScreenMainMenu(global)));
	}

	void Game::start()
	{
		while (global->window.isOpen())
		{
			elapsed_time = global_clock.restart();
			global->navigator.update();
			
			global->navigator.getScreen()->handle_input();
			global->navigator.getScreen()->update(elapsed_time);
			global->navigator.getScreen()->draw(elapsed_time);
		}
	}
}
