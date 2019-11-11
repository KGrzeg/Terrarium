#include "Game.hpp"
//#include "Screen.hpp"

namespace terr
{
	void Screen::setup(Game *game)
	{
		m_font = game->getDefaultFont();
		m_window_size = game->getWindowPtr()->getSize();
	}
}
