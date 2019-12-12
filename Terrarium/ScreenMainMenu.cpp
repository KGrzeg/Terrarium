#include "ScreenMainMenu.hpp"
#include "ScreenNewGame.hpp"
#include "ScreenLoadGame.hpp"

namespace terr {
	ScreenMainMenu::ScreenMainMenu(GlobalReference global) :
		ScreenMenu(global)
	{
		addPosition(L"Nowa Gra");
		addPosition(L"Wczytaj Grê");
		addPosition(L"Autor");
		addPosition(L"Pomoc");
		addPosition(L"Wyjœcie");
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
		case 4:
		{
			global->window.close();
			break;
		}
		}
	}


}
