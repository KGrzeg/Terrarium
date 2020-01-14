#pragma once
#include "ScreenMenu.hpp"
#include "Game.hpp"

namespace terr {
	class ScreenDeleteSaves :
		public terr::ScreenMenu
	{
	public:
		ScreenDeleteSaves(GlobalReference global);
		void clicked_option(int id) override;
	private:
		std::string names[DEFINED_MAPS] = {
			"Kopalnia", "Pustynia", "Ksiezyc", "Polana"
		};
	};

}