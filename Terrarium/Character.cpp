#include "Character.hpp"

namespace terr {
	Character::Character(GlobalReference global, World* world)
	{
		this->global = global;
		this->world = world;
		sprite = new AnimatedSprite(80, 80, global->assets.getTexture("game/character2"));
		sprite->setAnimation(3);
		sprite->setFPS(1.f / 12.f);
	}

	void Character::update(sf::Time& time) {
		sprite->update(time);
		handle_moving(time);
		handle_gravity(time);

		if (camera_follow) {
			auto v = global->window.getView();
			v.setCenter(getPosition());
			global->window.setView(v);
		}
	}

	void Character::handle_moving(sf::Time& time) {
		if (sf::Keyboard::isKeyPressed(key_move_left) &&
			!test_collision(SIDE_LEFT)) {
			move(-speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(key_move_right) &&
			!test_collision(SIDE_RIGHT)) {
			move(speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(key_move_up) &&
			!test_collision(SIDE_TOP)) {
			move(0, -speed * time.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(key_move_down) &&
			!test_collision(SIDE_DOWN)) {
			move(0, speed * time.asSeconds());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			world->move(0, 15);
		}
	}

	void Character::handle_gravity(sf::Time& time) {
		if (!test_collision(SIDE_DOWN)) {
			move(0, world->getGravity() * time.asSeconds());
		}
	}

	void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite);
	}

	bool Character::test_collision(int side) {
		return world->checkCollision(side_rectangle(side));
	}

	sf::FloatRect Character::side_rectangle(int side) {
		auto rectangle = sprite->getGlobalBounds();
		switch (side) {
		case SIDE_TOP: {
			rectangle.top -= collision_ray_distance;
			rectangle.height = collision_ray_thickness;
			break;
		}
		case SIDE_DOWN: {
			rectangle.top += collision_ray_distance + rectangle.height;
			rectangle.height = collision_ray_thickness;
			break;
		}
		case SIDE_LEFT: {
			rectangle.left -= collision_ray_distance;
			rectangle.width = collision_ray_thickness;
			break;
		}
		case SIDE_RIGHT: {
			rectangle.left += collision_ray_distance + rectangle.width;
			rectangle.width = collision_ray_thickness;
			break;
		}
		}

		return rectangle;
	}

}