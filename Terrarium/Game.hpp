#pragma once
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Navigator.hpp"
#include "AssetAdmin.hpp"
#include "Definitions.hpp"

namespace terr {
	enum game_screen_type
	{
		main,
		author,
		loadgame,
		newgame,
		help,
		game
	};

	struct GlobalData
	{
		sf::RenderWindow window;
		Navigator navigator;
		AssetAdmin assets;
	};
	typedef std::shared_ptr<GlobalData> GlobalReference;
	
	class Game
	{
	public:
		const std::string name = "Terrarium";
		const std::string version = "0.2";

		Game();

		void start();
		
	private:
		sf::Clock global_clock;
		sf::Time elapsed_time;
		
		GlobalReference global = std::make_shared<GlobalData>();
	};
	
}
