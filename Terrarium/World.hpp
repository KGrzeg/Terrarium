#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "PerlinNoise.hpp"

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#define TILE_AIR 0
#define TILE_DIRT 1
#define TILE_STONE 2
#define TILE_COAL 3

#define TILE_TYPES 4

#define MAX_LAYERS 10

namespace terr {
	typedef struct {
		int level = 40;
		int variation = 5;
		int tile_id = TILE_DIRT;
		float zoom = 1.0f;
		float treshold = 0.f;
		bool enabled = false;
	} WorldLayer;

	typedef struct
	{
		int width = 120;
		int height = 100;

		WorldLayer layers[MAX_LAYERS] = {
			{40, 9, TILE_DIRT, 14.2f, -2.f, true},
			{70, 16, TILE_STONE, 11.2f, -2.f, true},
			{60, 8, TILE_STONE, 4.f, 0.45f, true},
			{60, 8, TILE_COAL, 4.f, 0.75f, true}
		};

		int dirt_level = 55;
		float gravity = 185;
		float player_x = 100;
		float player_y = 20;
		std::string texture_name = "images/map_tileset.png";
	} WorldSettings;

	typedef struct {
		bool collide = false;
		int hardness = 1;
		int score = 0;
		sf::Vector2f texture_coords;
	} tile;

	class World : public sf::Drawable, public sf::Transformable
	{
	public:
		World(GlobalReference global, WorldSettings& settings);
		~World();

		bool checkCollision(sf::FloatRect rectangle);
		float getGravity() const { return gravity; }
		int dig(int x, int y, int power);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void generate_simple_world(WorldSettings& settings);
		void generate_complex_world(WorldSettings& settings);
		void generate_filled_layer(WorldLayer& layer);

		bool check_collision_with_tile(sf::FloatRect& rectangle, int x, int y);
		void change_tile(int x, int y, int tile_def_id);

		void setup_vertices();
		void setup_tiles_definitions();

		GlobalReference global;
		int width, height;
		int* tiles;
		tile tile_definitions[TILE_TYPES];
		float gravity;

		sf::Texture spritesheet;
		sf::VertexArray vertices;
		sf::Texture* tex;

		PerlinNoise perlin_noise;
	};

}