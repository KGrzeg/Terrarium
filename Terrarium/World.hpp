#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "PerlinNoise.hpp"

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#define TILE_AIR 0
#define TILE_GRASS 1
#define TILE_GRASS_DECAL 2
#define TILE_DIRT 3
#define TILE_STONE 4
#define TILE_COAL 5
#define TILE_IRON 6
#define TILE_GOLD 7
#define TILE_EMERALD 8
#define TILE_WOOD 9

#define TILE_TYPES 10
#define MAX_LAYERS 30

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
		int width = 420;
		int height = 300;
		float gravity = 485;
		std::string texture_name = "game/map1";
		float player_x = 100;
		float player_y = -500;

		WorldLayer layers[MAX_LAYERS] = {
			{45, 9, TILE_GRASS, 14.2f, -2.f, true},
			{65, 8, TILE_DIRT, 14.1f, -2.f, true},
			{90, 16, TILE_STONE, 11.2f, -2.f, true},
			//{150, 50, TILE_DIRT, 15.0f, -1.2f, true},
			{80, 8, TILE_STONE, 4.f, 0.45f, true},
			{80, 8, TILE_COAL, 4.f, 0.75f, true},
			{125, 20, TILE_STONE, 12.f, 0.65f, true},
			{125, 20, TILE_IRON, 12.f, 0.75f, true},
			{190, 8, TILE_STONE, 4.f, 0.55f, true},
			{190, 8, TILE_GOLD, 4.f, 0.80f, true},
			{260, 40, TILE_EMERALD, 4.f, 0.9f, true},
			{230, 40, TILE_EMERALD, 1.f, 0.9f, true}
		};

	} WorldSettings;

	typedef struct {
		bool collide = true;
		bool destroyable = true;
		int hardness = 1;
		int score = 0;
		sf::Vector2f texture_coords = { 1,1 };
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