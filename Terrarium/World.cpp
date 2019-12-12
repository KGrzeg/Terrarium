#include "World.hpp"

World::World(WorldSettings settings)
{
	this->width = settings.width;
	this->height = settings.height;

	tiles = new tile*[width];
	for (int x = 0; x < width; ++x)
	{
		tiles[x] = new tile[height];
	}

	//TODO: error handling
	spritesheet.loadFromFile("images/map_tileset.png");

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			tiles[x][y].rectangle_shape.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
			tiles[x][y].rectangle_shape.setPosition(x*TILE_WIDTH, y*TILE_HEIGHT);
			tiles[x][y].rectangle_shape.setTexture(&spritesheet);
			tiles[x][y].rectangle_shape.setTextureRect(sf::IntRect(12, 23, TILE_WIDTH, TILE_HEIGHT));
			tiles[x][y].type = dirt;
		}
	}
}


World::~World()
{
	for (int x = 0; x < width; ++x)
	{
		delete[] tiles[x];
	}
	delete[] tiles;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			target.draw(tiles[x][y].rectangle_shape);
		}
	}
}
