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
		perlin_noise.setSeed(rand());

		tex = &global->assets.getTexture(settings.spritesheet_texture_name);
		setup_tiles_definitions();

		tiles = new int[width * height];

		generate_complex_world(settings);
		generate_immortal_frame(settings);

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

	void World::generate_filled_layer(WorldLayer& layer) {
		if (!layer.enabled) return;

		for (int x = 0; x < width; ++x) {
			float noise_h = perlin_noise(x, 1, layer.zoom);
			int h = layer.level + noise_h * layer.variation;

			h = std::max(0, h);
			h = std::min(h, height);

			for (int y = h; y < height; ++y) {
				int i = x + y * width;

				float noise = perlin_noise(x, y, layer.zoom);
				if (noise > layer.treshold)
					tiles[i] = layer.tile_id;
			}
		}
	}

	void World::generate_immortal_frame(WorldSettings& settings)
	{
		if (!settings.immortal_frame) return;

		for (int x = 0; x < width; ++x) swap_by_immortal(x, height - 1);
		for (int y = 1; y < height - 1; ++y) swap_by_immortal(0, y);
		for (int y = 1; y < height - 1; ++y) swap_by_immortal(width - 1, y);
	}

	void World::swap_by_immortal(int x, int y)
	{
		int i = x + y * width;
		if (tiles[i] == TILE_AIR)
			tiles[i] = TILE_IMMORTAL_AIR;
		else
			tiles[i] = TILE_OBSIDIAN;
	}

	void World::generate_complex_world(WorldSettings& s) {

		for (int i = 0; i < width * height; i++)
		{
			tiles[i] = TILE_AIR;
		}

		for (int i = 0; i < MAX_LAYERS; i++)
		{
			generate_filled_layer(s.layers[i]);
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
		tile_definitions[TILE_AIR].destroyable = false;
		tile_definitions[TILE_AIR].hardness = 0;
		tile_definitions[TILE_AIR].texture_coords = sf::Vector2f(1, 23);

		tile_definitions[TILE_GRASS_DECAL].collide = false;
		tile_definitions[TILE_GRASS_DECAL].destroyable = false;
		tile_definitions[TILE_GRASS_DECAL].texture_coords = sf::Vector2f(12, 1);

		tile_definitions[TILE_GRASS].texture_coords = sf::Vector2f(12, 12);
		tile_definitions[TILE_GRASS].score = 1;
		tile_definitions[TILE_DIRT].texture_coords = sf::Vector2f(12, 23);
		tile_definitions[TILE_DIRT].score = 1;
		tile_definitions[TILE_SAND].texture_coords = sf::Vector2f(40, 12);
		tile_definitions[TILE_SAND].score = 1;
		tile_definitions[TILE_MOON_TORF].texture_coords = sf::Vector2f(1, 12);
		tile_definitions[TILE_MOON_TORF].score = 1;

		tile_definitions[TILE_STONE].hardness = 2;
		tile_definitions[TILE_STONE].score = 2;
		tile_definitions[TILE_STONE].texture_coords = sf::Vector2f(12, 34);

		tile_definitions[TILE_COAL].hardness = 2;
		tile_definitions[TILE_COAL].score = 4;
		tile_definitions[TILE_COAL].texture_coords = sf::Vector2f(12, 45);

		tile_definitions[TILE_IRON].hardness = 3;
		tile_definitions[TILE_IRON].score = 8;
		tile_definitions[TILE_IRON].texture_coords = sf::Vector2f(23, 1);

		tile_definitions[TILE_GOLD].hardness = 4;
		tile_definitions[TILE_GOLD].score = 16;
		tile_definitions[TILE_GOLD].texture_coords = sf::Vector2f(34, 1);

		tile_definitions[TILE_EMERALD].hardness = 5;
		tile_definitions[TILE_EMERALD].score = 48;
		tile_definitions[TILE_EMERALD].texture_coords = sf::Vector2f(45, 1);

		tile_definitions[TILE_DIAMOND].hardness = 6;
		tile_definitions[TILE_DIAMOND].score = 102;
		tile_definitions[TILE_DIAMOND].texture_coords = sf::Vector2f(69, 1);

		tile_definitions[TILE_IMMORTAL_AIR].collide = true;
		tile_definitions[TILE_IMMORTAL_AIR].destroyable = false;
		tile_definitions[TILE_IMMORTAL_AIR].texture_coords = sf::Vector2f(1, 23);

		tile_definitions[TILE_OBSIDIAN].collide = true;
		tile_definitions[TILE_OBSIDIAN].destroyable = false;
		tile_definitions[TILE_OBSIDIAN].texture_coords = sf::Vector2f(57, 1);

		tile_definitions[TILE_MOON_ROCK].hardness = 2;
		tile_definitions[TILE_MOON_ROCK].score = 2;
		tile_definitions[TILE_MOON_ROCK].texture_coords = sf::Vector2f(51, 12);

		tile_definitions[TILE_MOON_COAL].hardness = 2;
		tile_definitions[TILE_MOON_COAL].score = 4;
		tile_definitions[TILE_MOON_COAL].texture_coords = sf::Vector2f(62, 12);

		tile_definitions[TILE_MOON_IRON].hardness = 3;
		tile_definitions[TILE_MOON_IRON].score = 8;
		tile_definitions[TILE_MOON_IRON].texture_coords = sf::Vector2f(73, 12);

		tile_definitions[TILE_MOON_GOLD].hardness = 4;
		tile_definitions[TILE_MOON_GOLD].score = 16;
		tile_definitions[TILE_MOON_GOLD].texture_coords = sf::Vector2f(54, 23);

		tile_definitions[TILE_MOON_EMERALD].hardness = 5;
		tile_definitions[TILE_MOON_EMERALD].score = 48;
		tile_definitions[TILE_MOON_EMERALD].texture_coords = sf::Vector2f(65, 23);
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

		if (tile_def.destroyable && tile_def.hardness <= power) {
			change_tile(tile_x, tile_y, TILE_AIR);
			return tile_def.score;
		}

		return 0;
	}
	void World::makeSheepHole(int sheep_x)
	{
		for (int x = sheep_x - SHEEP_HOLE_SIZE; x < sheep_x + SHEEP_HOLE_SIZE; ++x)
			for (int y = height - SHEEP_HOLE_SIZE; y < height - 1; ++y) {
				change_tile(x, y, TILE_AIR);
			}
	}

	std::fstream& operator<<(std::fstream& os, const World& w)
	{
		for (size_t i = 0; i < w.width * w.height; i++)
			os << w.tiles[i] << ' ';

		os << std::endl;

		return os;
	}

	std::fstream& operator>>(std::fstream& os, World& w)
	{
		for (size_t i = 0; i < w.width * w.height; i++)
			os >> w.tiles[i];

		w.setup_vertices();
		return os;
	}

	std::fstream& operator<<(std::fstream& os, const WorldSettings& ws)
	{
		os << ws.name << std::endl;
		os << ws.difficulty << std::endl;
		os << ws.spritesheet_texture_name << std::endl;
		os << ws.background_texture_name << std::endl;

		os << ws.gravity << ' ';
		os << ws.width << ' ';
		os << ws.height << ' ';
		os << ws.player_x << ' ';
		os << ws.player_y << ' ';
		os << ws.initial_time << ' ';
		os << ws.default_power << ' ';
		os << ws.immortal_frame << std::endl;

		for (size_t i = 0; i < MAX_LAYERS; i++)
			os << ws.layers[i];

		return os;
	}

	std::fstream& operator>>(std::fstream& os, WorldSettings& ws)
	{
		os >> ws.name;
		os >> ws.difficulty;
		os >> ws.spritesheet_texture_name;
		os >> ws.background_texture_name;

		os >> ws.gravity;
		os >> ws.width;
		os >> ws.height;
		os >> ws.player_x;
		os >> ws.player_y;
		os >> ws.initial_time;
		os >> ws.default_power;
		os >> ws.immortal_frame;

		for (size_t i = 0; i < MAX_LAYERS; i++)
			os >> ws.layers[i];

		return os;
	}

	std::fstream& operator<<(std::fstream& os, const WorldLayer& wl) {
		os << wl.enabled << ' ';
		os << wl.level << ' ';
		os << wl.tile_id << ' ';
		os << wl.treshold << ' ';
		os << wl.variation << ' ';
		os << wl.zoom << std::endl;
		return os;
	}

	std::fstream& operator>>(std::fstream& os, WorldLayer& wl)
	{
		os >> wl.enabled;
		os >> wl.level;
		os >> wl.tile_id;
		os >> wl.treshold;
		os >> wl.variation;
		os >> wl.zoom;
		return os;
	}
}