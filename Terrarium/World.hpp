#pragma once
#include <SFML/Graphics.hpp>

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

enum tile_type
{
	dirt,
	stone
};

typedef struct
{
	sf::RectangleShape rectangle_shape;
	tile_type type;
} tile;

class World : public sf::Drawable
{
public:
	World(int width, int height);
	~World();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	int width, height;
	tile **tiles;
	sf::Texture spritesheet;
};

