#pragma once
#include <SFML/Graphics.hpp>

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

namespace terr {
	typedef struct
	{
		int width;
		int height;
	} WorldSettings;

	enum tile_type
	{
		dirt,
		stone,
		air
	};

	typedef struct
	{
		sf::RectangleShape rectangle_shape;
		tile_type type;
		bool collide = true;
	} tile;

	class World : public sf::Drawable
	{
	public:
		World(WorldSettings settings);
		~World();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool checkCollision(sf::FloatRect rectangle);
		
	private:
		tile gen_tile(int x, int y);
		tile gen_dirt(int x, int y);
		tile gen_stone(int x, int y);
		tile gen_air(int x, int y);

		int width, height;
		tile** tiles;
		sf::Texture spritesheet;
	};

}