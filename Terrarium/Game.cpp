#include "Game.hpp"
#include "ScreenMainMenu.hpp"

namespace terr {
	Game::Game()
	{
		global->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
			name + " v" + version,
			sf::Style::Default);

		global->window.setVerticalSyncEnabled(true);

		global->assets.addFont("default", "arial.ttf");
		global->assets.addTexture("menu/background", "images/menu_background.jpg");
		global->assets.addTexture("game/character", "images/character_spritesheet.png");
		global->assets.addTexture("game/character2", "images/character_spritesheet2.png");
		global->assets.addTexture("game/map1", "images/map_tileset.png");
		global->assets.addTexture("ui/topbar", "images/info_bar.png");
		global->assets.addTexture("ui/tools", "images/tools.png");

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
