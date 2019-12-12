#include "ScreenMainMenu.hpp"



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
}
