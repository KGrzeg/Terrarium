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

	void Character::update(sf::Time time) {
		sprite->update(time);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!world->checkCollision(side_rectangle(SIDE_LEFT))) {
			move(-speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			!world->checkCollision(side_rectangle(SIDE_RIGHT))) {
			move(speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!world->checkCollision(side_rectangle(SIDE_TOP))) {
			move(0, -speed * time.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!world->checkCollision(side_rectangle(SIDE_DOWN))) {
			move(0, speed * time.asSeconds());
		}
	}

	void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite);
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