#pragma once
#include "Screen.hpp"
#include "World.hpp"


class ScreenPlay :
	public terr::Screen
{
public:
	ScreenPlay(int width, int height);
	~ScreenPlay();
	void draw(sf::RenderWindow& window) override;
	void setup(terr::Game* game) override {};
	void update(terr::Game* game) override {};
private:
	World world;
};

