#include <random>
#include <ctime>
#include <iostream>

#include "World.hpp"

namespace terr {
	World::World(GlobalReference global, WorldSettings& settings)
	{
		this->global = global;
		this->width = settings.width;
		this->height = settings.height;
		this->gravity = settings.gravity;

		srand(time(0));

		tex = &global->assets.addTexture("map_spritesheet", settings.texture_name);
		setup_tiles_definitions();

		tiles = new int[width * height];
		//generate_simple_world(settings);
		generate_complex_world(settings);
		setup_vertices();
	}

	World::~World()
	{
		delete[] tiles;
	}

	void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = tex;

		// draw the vertex array
		target.draw(vertices, states);
	}

	void World::generate_simple_world(WorldSettings& settings) {

		int x, y;
		for (int i = 0; i < width * height; i++)
		{
			x = i % width;
			y = i / width;

			if (y < settings.surface_level) {
				tiles[i] = TILE_AIR;
				continue;
			}

			if (y < settings.dirt_level) {
				tiles[i] = TILE_DIRT;
				continue;
			}

			tiles[i] = TILE_STONE;
		}
	}

	void World::generate_complex_world(WorldSettings& s) {
		perlin_noise.setSeed(rand());

		//TODO: to delete
		for (int i = 0; i < width * height; i++)
		{
			tiles[i] = TILE_AIR;
		}

		//surface
		for (int x = 0; x < width; ++x) {
			float noise = perlin_noise(x, 1, s.surface_zoom);
			int sur_height = s.surface_level + noise * s.surface_variation;

			for (int y = sur_height; y < height; ++y) {
				int i = x + y * width;
				tiles[i] = TILE_DIRT;
			}
		}
	}

	void World::setup_vertices() {
		vertices.setPrimitiveType(sf::Quads);
		vertices.resize(width * height * 4);

		int x, y;
		for (int i = 0; i < width * height; i++)
		{
			x = i % width;
			y = i / width;

			sf::Vertex* quad = &vertices[i * 4];

			//quad position
			quad[0].position = sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT);
			quad[1].position = sf::Vector2f((x + 1) * TILE_WIDTH, y * TILE_HEIGHT);
			quad[2].position = sf::Vector2f((x + 1) * TILE_WIDTH, (y + 1) * TILE_HEIGHT);
			quad[3].position = sf::Vector2f(x * TILE_WIDTH, (y + 1) * TILE_HEIGHT);

			//texture position
			auto tex_coords = tile_definitions[tiles[i]].texture_coords;
			quad[0].texCoords = sf::Vector2f(tex_coords.x, tex_coords.y);
			quad[1].texCoords = sf::Vector2f(tex_coords.x + TILE_WIDTH, tex_coords.y);
			quad[2].texCoords = sf::Vector2f(tex_coords.x + TILE_WIDTH, tex_coords.y + TILE_HEIGHT);
			quad[3].texCoords = sf::Vector2f(tex_coords.x, tex_coords.y + TILE_HEIGHT);
		}
	}

	bool World::check_collision_with_tile(sf::FloatRect& rectangle, int x, int y) {
		const int tile_min_x = x * TILE_WIDTH + getPosition().x;
		const int tile_max_x = tile_min_x + TILE_WIDTH;
		const int tile_min_y = y * TILE_HEIGHT + getPosition().y;
		const int tile_max_y = tile_min_y + TILE_HEIGHT;

		if (rectangle.left + rectangle.width < tile_min_x)
			return false;

		if (rectangle.left > tile_max_x)
			return false;

		if (rectangle.top + rectangle.height < tile_min_y)
			return false;

		if (rectangle.top > tile_max_y)
			return false;

		return true;
	}

	bool World::checkCollision(sf::FloatRect rectangle) {
		int x, y;
		for (int i = 0; i < width * height; i++)
		{
			x = i % width;
			y = i / width;

			auto tile_def = tile_definitions[tiles[i]];

			if (!tile_def.collide)
				continue;

			if (check_collision_with_tile(rectangle, x, y))
				return true;
		}
		return false;
	}

	void World::setup_tiles_definitions() {
		tile_definitions[TILE_AIR].collide = false;
		tile_definitions[TILE_AIR].hardness = 0;
		tile_definitions[TILE_AIR].texture_coords = sf::Vector2f(1, 23);


		tile_definitions[TILE_DIRT].collide = true;
		tile_definitions[TILE_DIRT].hardness = 1;
		tile_definitions[TILE_DIRT].texture_coords = sf::Vector2f(12, 23);

		tile_definitions[TILE_STONE].collide = true;
		tile_definitions[TILE_STONE].hardness = 2;
		tile_definitions[TILE_STONE].score = 1;
		tile_definitions[TILE_STONE].texture_coords = sf::Vector2f(12, 34);
	}

	void World::change_tile(int x, int y, int tile_def_id) {
		const int id = x + y * width;
		auto tex_coords = tile_definitions[tile_def_id].texture_coords;

		tiles[id] = tile_def_id;

		//update texture coords
		vertices[id * 4 + 0].texCoords = sf::Vector2f(tex_coords.x, tex_coords.y);
		vertices[id * 4 + 1].texCoords = sf::Vector2f(tex_coords.x + TILE_WIDTH, tex_coords.y);
		vertices[id * 4 + 2].texCoords = sf::Vector2f(tex_coords.x + TILE_WIDTH, tex_coords.y + TILE_HEIGHT);
		vertices[id * 4 + 3].texCoords = sf::Vector2f(tex_coords.x, tex_coords.y + TILE_HEIGHT);
	}

	int World::dig(int x, int y, int power) {
		//world coords to tilemap coords
		const int tile_x = x / TILE_WIDTH;
		const int tile_y = y / TILE_HEIGHT;

		if (tile_x < 0 || tile_x > width)
			return false;
		if (tile_y < 0 || tile_y > height)
			return false;

		tile tile_def = tile_definitions[tiles[tile_x + tile_y * width]];

		if (tile_def.hardness <= power) {
			change_tile(tile_x, tile_y, TILE_AIR);
			return tile_def.score;
		}

		return 0;
	}
}