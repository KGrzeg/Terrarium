#include "ScreenMainMenu.hpp"
#include "Button.hpp"

void terr::ScreenMainMenu::setup(Game* game)
{
	ScreenMenu::setup(game);

	/*AddElement(new Button(game->getDefaultFont(), L"Zacznij grê"));
	AddElement(new Button(game->getDefaultFont(), L"Wczytaj grê"));
	AddElement(new Button(game->getDefaultFont(), L"Pomoc"));
	AddElement(new Button(game->getDefaultFont(), L"Ustawienia"));
	AddElement(new Button(game->getDefaultFont(), L"O autorze"));
	AddElement(new Button(game->getDefaultFont(), L"Wyjscie"));*/
}

void terr::ScreenMainMenu::draw(sf::RenderWindow&)
{
}

void terr::ScreenMainMenu::update()
{
}
