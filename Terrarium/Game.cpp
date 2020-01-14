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
		global->assets.addFont("fancy", "AnotherRound.otf");

		global->assets.addTexture("menu/background", "images/menu_background.jpg");
		global->assets.addTexture("menu/background_main", "images/menu_background_main.jpg");

		global->assets.addTexture("help", "images/help_screen.jpg");
		global->assets.addTexture("win", "images/win_info.jpg");
		global->assets.addTexture("defeat", "images/defeat_info.jpg");

		global->assets.addTexture("game/character", "images/character_spritesheet.png");
		global->assets.addTexture("game/character2", "images/character_spritesheet2.png");
		global->assets.addTexture("game/character3", "images/dwarf.png");
		global->assets.addTexture("game/map1", "images/map_tileset.png");
		global->assets.addTexture("game/skyBlue", "images/background_blue_sky.jpg").setRepeated(true);
		global->assets.addTexture("game/skyYellow", "images/background_yellow_sky.jpg").setRepeated(true);
		global->assets.addTexture("game/skySpace", "images/background_space_sky.jpg").setRepeated(true);

		global->assets.addTexture("ui/topbar", "images/info_bar.png");
		global->assets.addTexture("ui/tools", "images/drills.png");
		global->assets.addTexture("ui/hourglass", "images/hourglass.png");

		global->navigator.pushScreen(ScreenReference(new ScreenMainMenu(global)));
	}

	void Game::start()
	{
		while (global->window.isOpen())
		{
			global->navigator.update();
			elapsed_time = global_clock.restart();

			global->navigator.getScreen()->handle_input();
			global->navigator.getScreen()->update(elapsed_time);
			global->navigator.getScreen()->draw(elapsed_time);
		}
	}
}
