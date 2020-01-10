#pragma once
#include "Screen.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Character.hpp"
#include "Pickaxe.hpp"

namespace terr {
	class ScreenPlay :
		public terr::Screen
	{
	public:
		ScreenPlay(GlobalReference global, WorldSettings settings);
		~ScreenPlay() {
			delete player;
		}
		void draw(sf::Time time) override;
		void update(sf::Time time) override;
		void handle_input() override;

	private:
		const float update_fps = 1.f / 60.f;
		sf::Time update_elapsed_time;
		GlobalReference global;
		World world;
		Character* player;
		sf::Text fps_meter;
		Pickaxe pickaxe;
	};
}