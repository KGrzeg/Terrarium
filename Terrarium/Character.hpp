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
		Character(GlobalReference global, World* world);
		~Character() {
			delete sprite;
		};

		void update(sf::Time& time);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void handle_event(sf::Event& event);

		void move(float x, float y) { sprite->move(x, y); }
		void setPosition(float x, float y) { sprite->setPosition(x, y); }

		sf::Vector2f getPosition() const { return sprite->getPosition(); }
		sf::Sprite* getSprite() { return sprite->getSprite(); };

	private:
		const float jump_power = 420;
		const float speed = 160;
		const float speed_in_air = speed;
		const float collision_ray_distance = 1.f;
		const float collision_ray_thickness = 0.5f;
		const float collision_ray_shrink = 0.8f;
		const float zoom_step = 0.1f;
		const float zoom_min = 0.2f;
		const float zoom_max = 1.f;

		void handle_moving(sf::Time& time);
		void handle_gravity(sf::Time& time);
		void handle_velocity(sf::Time& time);
		bool test_collision(int side);
		sf::FloatRect side_rectangle(int side);

		AnimatedSprite* sprite;
		World* world;
		GlobalReference global;

		sf::Vector2f velocity;

		bool camera_follow = true;
		bool jumping = false;
		bool move_horizontally = false;
		bool god_mode = false;
		bool allow_zoom = true;
		bool on_ground = false;

		float zoom;
		sf::View view;

		sf::Keyboard::Key key_move_up = sf::Keyboard::W;
		sf::Keyboard::Key key_move_down = sf::Keyboard::S;
		sf::Keyboard::Key key_move_left = sf::Keyboard::A;
		sf::Keyboard::Key key_move_right = sf::Keyboard::D;
	};
}