#include "ScreenLoadGame.hpp"


namespace terr {
	ScreenLoadGame::ScreenLoadGame(GlobalReference global) :
		ScreenMenu(global)
	{
		addPosition(L"Slot 1");
		addPosition(L"Slot 2");
		addPosition(L"Slot 3");
		addPosition(L"Slot 4");
		addPosition(L"Slot 5");
		addPosition(L"Powrót");
	}

	void ScreenLoadGame::clicked_option(int id)
	{
		switch (id)
		{
		case 5:
		{
			global->navigator.goBack();
			break;
		}
		}
	}

}