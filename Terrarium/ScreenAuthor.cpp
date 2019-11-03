#include "ScreenAuthor.hpp"
#include "Button.hpp"

void terr::ScreenAuthor::setup(Game* game)
{
	ScreenMenu::setup(game);

	sf::Font f = game->getDefaultFont();
	
	AddElement(new UIElement(f, L"Autor Gry"));
	AddElement(new UIElement(f, L"Grzegorz Kupczyk"));
	AddElement(new Button(f, L"Wróæ"));
	AddElement(new Button(f, L"Wyjscie"));
}

void terr::ScreenAuthor::draw(sf::RenderWindow&)
{
}

void terr::ScreenAuthor::update()
{
}
