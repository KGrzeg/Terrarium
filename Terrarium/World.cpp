#include "World.hpp"
#include <random>
#include <ctime>

namespace terr {
	World::World(WorldSettings settings)
	{
		this->width = settings.width;
		this->height = settings.height;
		srand(time(nullptr));

		tiles = new tile * [width];
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
				switch (rand() % 20) {
				case 0: {
					tiles[x][y] = gen_dirt(x, y);
					break;
				}
				case 1: {
					tiles[x][y] = gen_stone(x, y);
					break;
				}
				default: {
					tiles[x][y] = gen_air(x, y);
					break;
				}
				}
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

	bool World::checkCollision(sf::FloatRect rectangle) {
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				if (!tiles[x][y].collide)
					continue;

				bool intersecting = tiles[x][y]
					.rectangle_shape
					.getGlobalBounds()
					.intersects(rectangle);

				if (intersecting) {
					return true;
				}
			}
		}
		return false;
	}
	tile World::gen_tile(int x, int y) {
		tile tileInstance;

		tileInstance.rectangle_shape.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
		tileInstance.rectangle_shape.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
		tileInstance.rectangle_shape.setTexture(&spritesheet);

		return tileInstance;
	}

	tile World::gen_dirt(int x, int y) {
		tile tileInstance = gen_tile(x, y);

		tileInstance.rectangle_shape.setTextureRect(sf::IntRect(12, 23, TILE_WIDTH, TILE_HEIGHT));
		tileInstance.type = dirt;

		return tileInstance;
	}

	tile World::gen_stone(int x, int y) {
		tile tileInstance = gen_tile(x, y);

		tileInstance.rectangle_shape.setTextureRect(sf::IntRect(12, 34, TILE_WIDTH, TILE_HEIGHT));
		tileInstance.type = stone;

		return tileInstance;
	}

	tile World::gen_air(int x, int y) {
		tile tileInstance = gen_tile(x, y);

		tileInstance.rectangle_shape.setTextureRect(sf::IntRect(1, 23, TILE_WIDTH, TILE_HEIGHT));
		tileInstance.type = air;
		tileInstance.collide = false;

		return tileInstance;
	}
}