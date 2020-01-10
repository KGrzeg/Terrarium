#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "AnimatedSprite.hpp"
#include "World.hpp"

#define SIDE_TOP 1
#define SIDE_DOWN 2
#define SIDE_LEFT 3
#define SIDE_RIGHT 4

namespace terr {
	class Character : public sf::Drawable
	{
	public:
		Character(GlobalReference global, World *world);
		~Character() {
			delete sprite;
		};
		
		void update(sf::Time time);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void move(float x, float y) { sprite->move(x, y); }
		void setPosition(float x, float y) { sprite->setPosition(x, y); }

		sf::Vector2f getPosition() const { return sprite->getPosition(); }
		sf::Sprite* getSprite() { return sprite->getSprite(); };
		

	private:
		sf::FloatRect side_rectangle(int side);

		AnimatedSprite *sprite;
		World *world;
		GlobalReference global;

		const float speed = 115;
		const float collision_ray_distance = 2.f;
		const float collision_ray_thickness = 1.f;
	};
}