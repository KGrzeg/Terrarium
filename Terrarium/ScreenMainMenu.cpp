#include "ScreenMainMenu.hpp"
#include "ScreenNewGame.hpp"
#include "ScreenLoadGame.hpp"

namespace terr {
	ScreenMainMenu::ScreenMainMenu(GlobalReference global) :
		ScreenMenu(global)
	{
		addPosition(L"Nowa Gra");
		addPosition(L"Wczytaj Gre");
		addPosition(L"Wyjscie");
	}

	void ScreenMainMenu::clicked_option(int id)
	{
		switch (id)
		{
		case 0:
		{
			global->navigator.pushScreen(ScreenReference(new ScreenNewGame(global)));
			break;
		}
		case 1:
		{
			global->navigator.pushScreen(ScreenReference(new ScreenLoadGame(global)));
			break;
		}
		case 2:
		{
			global->window.close();
			break;
		}
		}
	}


}
