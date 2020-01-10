#pragma once
#include "Screen.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "AnimatedSprite.hpp"

namespace terr {
	class ScreenPlay :
		public terr::Screen
	{
	public:
		ScreenPlay(GlobalReference global, WorldSettings settings);
		~ScreenPlay() {
			delete animeddd;
		}
		void draw(sf::Time time) override;
		void update(sf::Time time) override;
		void handle_input() override {};

	private:
		GlobalReference global;
		World world;
		AnimatedSprite* animeddd = nullptr;
	};
}