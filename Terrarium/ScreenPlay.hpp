#pragma once
#include "Screen.hpp"
#include "World.hpp"
#include "Game.hpp"

namespace terr {
	class ScreenPlay :
		public terr::Screen
	{
	public:
		ScreenPlay(GlobalReference global, WorldSettings settings);
		void draw(sf::Time time);
	private:
		GlobalReference global;
		World world;
	};
}