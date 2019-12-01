#include "ScreenPlay.hpp"


ScreenPlay::ScreenPlay(int width, int height) :
	world(width, height)
{
}


ScreenPlay::~ScreenPlay()
{
}

void ScreenPlay::draw(sf::RenderWindow& window)
{
	window.draw(world);
}
