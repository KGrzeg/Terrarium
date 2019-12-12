#pragma once
#include "ScreenMenu.hpp"
#include "Game.hpp"

namespace terr{
class ScreenMainMenu :
	public terr::ScreenMenu
{
public:
	ScreenMainMenu(GlobalReference global);
};

}