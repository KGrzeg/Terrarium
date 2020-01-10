#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#define TILE_AIR 0
#define TILE_DIRT 1
#define TILE_STONE 2

#define TILE_TYPES 3

namespace terr {
	typedef struct
	{
		int width = 520;
		int height = 300;
		int surface_level = 40;
		int dirt_level = 55;
		float gravity = 35;
		std::string texture_name = "images/map_tileset.png";
	} WorldSettings;

	typedef struct {
		bool collide = false;
		int hardness = 1;
		sf::Vector2f texture_coords;
	} tile;

	class World : public sf::Drawable, public sf::Transformable
	{
	public:
		World(GlobalReference global, WorldSettings& settings);
		~World();

		bool checkCollision(sf::FloatRect rectangle);
		float getGravity() const { return gravity; }

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void generate_simple_world(WorldSettings& settings);
		bool check_collision_with_tile(sf::FloatRect& rectangle, int x, int y);

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
	};

}