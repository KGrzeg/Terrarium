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

		if (!god_mode)
			handle_gravity(time);
		handle_velocity(time);

		if (camera_follow) {
			view.setCenter(
				getPosition().x + getSprite()->getGlobalBounds().width / 2,
				getPosition().y + getSprite()->getGlobalBounds().height / 2
			);
			global->window.setView(view);
		}
	}

	void Character::handle_event(sf::Event& event) {
		if (allow_zoom)
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.delta > 0) {
					zoom -= zoom_step;
				}
				else {
					zoom += zoom_step;
				}
				zoom = std::max(zoom_min, zoom);
				zoom = std::min(zoom_max, zoom);

				view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

				view.zoom(zoom);
				global->window.setView(view);
			}
	}

	void Character::handle_moving(sf::Time& time) {
		move_horizontally = false;

		if (god_mode) {
			if (sf::Keyboard::isKeyPressed(key_move_left)) {
				velocity.x = -speed;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_right)) {
				velocity.x = speed;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_up)) {
				velocity.y = -speed;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_down)) {
				velocity.y = speed;
				move_horizontally = true;
			}
			if (!move_horizontally) {
				velocity.x = 0;
				velocity.y = 0;
			}

		}
		else {
			if (sf::Keyboard::isKeyPressed(key_move_left) &&
				!test_collision(SIDE_LEFT)) {
				velocity.x = -speed;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_right) &&
				!test_collision(SIDE_RIGHT)) {
				velocity.x = speed;
				move_horizontally = true;
			}

			if (sf::Keyboard::isKeyPressed(key_move_up) &&
				!jumping &&
				!test_collision(SIDE_TOP)) {
				jumping = true;
				velocity.y -= jump_power;
			}
			if (!move_horizontally) {
				velocity.x = 0;
			}
		}

	}

	void Character::handle_gravity(sf::Time& time) {
		if (test_collision(SIDE_DOWN)) {
			if (velocity.y > 0) {

				velocity.y = 0;
				if (jumping) jumping = false;
			}
		}
		else {
			velocity.y += world->getGravity() * time.asSeconds();
		}
	}

	void Character::handle_velocity(sf::Time& time) {
		move(velocity.x * time.asSeconds(), velocity.y * time.asSeconds());
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

			float w = rectangle.width;
			rectangle.width *= collision_ray_shrink;
			rectangle.left += (w - rectangle.width) / 2;
			break;
		}
		case SIDE_DOWN: {
			rectangle.top += collision_ray_distance + rectangle.height;
			rectangle.height = collision_ray_thickness;

			float w = rectangle.width;
			rectangle.width *= collision_ray_shrink;
			rectangle.left += (w - rectangle.width) / 2;
			break;
		}
		case SIDE_LEFT: {
			rectangle.left -= collision_ray_distance;
			rectangle.width = collision_ray_thickness;

			float h = rectangle.height;
			rectangle.height *= collision_ray_shrink;
			rectangle.top += (h - rectangle.height) / 2;
			break;
		}
		case SIDE_RIGHT: {
			rectangle.left += collision_ray_distance + rectangle.width;
			rectangle.width = collision_ray_thickness;

			float h = rectangle.height;
			rectangle.height *= collision_ray_shrink;
			rectangle.top += (h - rectangle.height) / 2;
			break;
		}
		}

		return rectangle;
	}

}