#include "ScreenMainMenu.hpp"
#include "ScreenNewGame.hpp"
#include "ScreenDeleteSaves.hpp"

namespace terr {
	ScreenMainMenu::ScreenMainMenu(GlobalReference global) :
		ScreenMenu(global)
	{
		addPosition("");
		addPosition("");
		addPosition(L"Nowa Gra");
		addPosition(L"Usun Zapis");
		addPosition(L"Wyjscie");

		m_background_shape.setTexture(&global->assets.getTexture("menu/background_main"));
		m_background_shape.setTextureRect({ 0,0,WINDOW_WIDTH, WINDOW_HEIGHT });
	}

	void ScreenMainMenu::clicked_option(int id)
	{
		switch (id)
		{
		case 2:
		{
			global->navigator.pushScreen(ScreenReference(new ScreenNewGame(global)));
			break;
		}
		case 3:
		{
			global->navigator.pushScreen(ScreenReference(new ScreenDeleteSaves(global)));
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
