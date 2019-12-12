#pragma once
#include "ScreenMenu.hpp"
#include "Game.hpp"

namespace terr {
	class ScreenLoadGame :
		public terr::ScreenMenu
	{
	public:
		ScreenLoadGame(GlobalReference global);
		void clicked_option(int id) override;
	};

}