#include "ScreenMainMenu.hpp"



namespace terr {
	ScreenMainMenu::ScreenMainMenu(GlobalReference global) :
		ScreenMenu(global)
	{		
		addPosition(L"Nowa Gra");
		addPosition(L"Wczytaj Gr�");
		addPosition(L"Autor");
		addPosition(L"Pomoc");
		addPosition(L"Wyj�cie");
	}
}
