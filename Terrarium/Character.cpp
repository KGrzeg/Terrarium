#include <iostream>
#include "Character.hpp"

namespace terr {
	Character::Character(GlobalReference global, World* world)
	{
		this->global = global;
		this->world = world;

		sprite_setup(global);

		view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		view.zoom(zoom);
	}

	void Character::sprite_setup(terr::GlobalReference& global)
	{
		AnimationFrameDef* frames = new AnimationFrameDef[64]{
		{ 7, 11, 24, 19 },
		{ 44, 13, 26, 17 },
		{ 83, 12, 24, 18 },
		{ 121, 11, 24, 19 },
		{ 159, 10, 24, 20 },
		{ 6,43,26,19 },
		{ 43,42,27,19 },
		{ 82,43,26,19 },
		{ 121,45,24,18 },
		{ 160,44,22,19 },
		{ 199,43,20,19 },
		{ 236,43,22,19 },
		{ 273,45,24,18 },
		{ 7,75,24,19 },
		{ 48,68,13,23 },
		{ 85,67,14,24 },
		{ 123,68,23,22 },
		{ 162,76,19,21 },
		{ 200,76,17,21 },
		{ 236,77,22,17 },
		{ 7,171,24,19 },
		{ 44,170,26,19 },
		{ 81,166,26,19 },
		{ 120,165,26,20 },
		{ 159,173,24,17 },
		{ 8,235,24,19 },
		{ 45,236,26,18 },
		{ 83,237,26,17 },
		{ 121,238,26,16 },
		{ 159,241,26,13 },
		{ 198,241,27,13 },
		{ 236,242,29,13 },
		{ 2,267,24,19 },
		{ 39,269,26,17 },
		{ 78,268,24,18 },
		{ 116,267,24,19 },
		{ 154,266,24,20 },
		{ 1,299,26,19 },
		{ 39,298,27,19 },
		{ 77,299,26,19 },
		{ 116,301,24,18 },
		{ 155,300,22,19 },
		{ 194,300,20,19 },
		{ 231,300,22,19 },
		{ 268,301,24,18 },
		{ 2,331,24,19 },
		{ 48,324,13,23 },
		{ 86,323,14,24 },
		{ 115,324,23,22 },
		{ 156,332,19,21 },
		{ 196,333,17,21 },
		{ 231,334,22,17 },
		{ 2,427,24,19 },
		{ 39,426,26,19 },
		{ 78,422,26,19 },
		{ 115,421,26,20 },
		{ 154,429,24,17 },
		{ 1, 491, 24, 19 },
		{ 38, 492, 26, 18 },
		{ 76, 493, 26, 17 },
		{ 114, 494, 26, 16 },
		{ 152, 497, 26, 13 },
		{ 188, 498, 27, 13 },
		{ 224, 499, 29, 13 },
		};
		AnimationDef* animations = new AnimationDef[10]{
			//right
			{ 0, 4 }, //idle
		{ 5, 12 }, //walk
		{ 13, 19, true, ANIMATION_IDLE, 12.f }, //mine
		{ 20, 24 }, //jump
		{ 25, 31 }, //dead
					//left
		{ 32, 36 },
		{ 37, 44 },
		{ 45, 51, true, ANIMATION_IDLE + ANIMATION_SIDE_OFFSET, 12.f },
		{ 52, 56 },
		{ 56, 63 }
		};

		sprite = new AnimatedSprite(animations, frames);
		sprite->setTexture(global->assets.getTexture("game/character3"));
		sprite->setFPS(6.f);
	}

	void Character::update(sf::Time& time) {
		handle_gravity(time);

		handle_moving(time);
		handle_velocity(time);

		update_view();
		update_animation(time);
	}

	void Character::update_view()
	{
		if (!camera_follow)
			return;

		float cam_x = std::max(getPosition().x, view.getSize().x / 2.f);
		float cam_y = std::max(getPosition().y, view.getSize().y / 2.f);

		cam_x = std::min(cam_x, world->getSizeInPixels().x - view.getSize().x / 2.f);
		cam_y = std::min(cam_y, world->getSizeInPixels().y - view.getSize().y / 2.f);

		view.setCenter(cam_x, cam_y);
		global->window.setView(view);
	}

	void Character::handle_event(sf::Event& event) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::F12 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				god_mode = !god_mode;
				sprite->setColor(god_mode ? sf::Color::Yellow : sf::Color::White);
			}
		}

		if (allow_zoom)
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.delta > 0) zoom -= zoom_step;
				else zoom += zoom_step;

				zoom = std::max(zoom_min, zoom);
				zoom = std::min(zoom_max, zoom);

				view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

				view.zoom(zoom);
				global->window.setView(view);
			}
	}

	void Character::playMineAnimation()
	{
		int anim_id = ANIMATION_MINE;
		if (face_direction == SIDE_LEFT) anim_id += ANIMATION_SIDE_OFFSET;

		sprite->playAnimation(anim_id, true);
	}

	void Character::handle_moving(sf::Time& time) {
		move_horizontally = false;

		if (god_mode) {
			if (sf::Keyboard::isKeyPressed(key_move_left)) {
				velocity.x = -speed;
				face_direction = SIDE_LEFT;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_right)) {
				velocity.x = speed;
				face_direction = SIDE_RIGHT;
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
				velocity.x = on_ground ? -speed : -speed_in_air;
				face_direction = SIDE_LEFT;
				move_horizontally = true;
			}
			if (sf::Keyboard::isKeyPressed(key_move_right) &&
				!test_collision(SIDE_RIGHT)) {
				velocity.x = on_ground ? speed : speed_in_air;
				face_direction = SIDE_RIGHT;
				move_horizontally = true;
			}

			if (sf::Keyboard::isKeyPressed(key_move_up) &&
				on_ground && velocity.y >= 0) {
				velocity.y = -jump_power;
			}
			if (!move_horizontally) {
				velocity.x = 0;
			}
		}

	}

	void Character::handle_gravity(sf::Time& time) {
		if (velocity.y > 0 && !god_mode && test_collision(SIDE_DOWN, velocity.y * time.asSeconds() - collision_ray_distance)) {
			velocity.y = 0;
		}

		if (test_collision(SIDE_DOWN)) {
			//if falling
			on_ground = true;
		}
		else
		{
			//add gravity pull to down
			if (!god_mode) velocity.y += world->getGravity() * time.asSeconds();
			on_ground = false;
		}
	}

	void Character::handle_velocity(sf::Time& time) {
		if (!god_mode && velocity.y < 0 && test_collision(SIDE_TOP)) {
			velocity.y = 0;
		}

		move(velocity.x * time.asSeconds(), velocity.y * time.asSeconds());
	}

	void Character::update_animation(sf::Time& time)
	{
		int current_animation = ANIMATION_IDLE;
		if (velocity.x != 0) current_animation = ANIMATION_WALK;
		if (!on_ground) current_animation = ANIMATION_JUMP;

		//flip sides
		if (face_direction == SIDE_LEFT) current_animation += ANIMATION_SIDE_OFFSET;

		if (sprite->getCurrentAnimation() != ANIMATION_MINE && current_animation != last_animation_id) {
			sprite->playAnimation(current_animation, true);
			last_animation_id = current_animation;
		}

		sprite->update(time);
	}

	void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite);
	}

	bool Character::test_collision(int side, float additional_push) {
		return world->checkCollision(side_rectangle(side, additional_push));
	}

	sf::FloatRect Character::side_rectangle(int side, float additional_push) {
		auto rectangle = sprite->getGlobalBounds();
		switch (side) {
		case SIDE_TOP: {
			rectangle.top -= collision_ray_distance + additional_push;
			rectangle.height = collision_ray_thickness;

			float w = rectangle.width;
			rectangle.width *= collision_ray_shrink;
			rectangle.left += (w - rectangle.width) / 2;
			break;
		}
		case SIDE_DOWN: {
			rectangle.top += collision_ray_distance + rectangle.height + additional_push;
			rectangle.height = collision_ray_thickness;

			float w = rectangle.width;
			rectangle.width *= collision_ray_shrink;
			rectangle.left += (w - rectangle.width) / 2;
			break;
		}
		case SIDE_LEFT: {
			rectangle.left -= collision_ray_distance + additional_push;
			rectangle.width = collision_ray_thickness;

			float h = rectangle.height;
			rectangle.height *= collision_ray_shrink;
			rectangle.top += (h - rectangle.height) / 2;
			break;
		}
		case SIDE_RIGHT: {
			rectangle.left += collision_ray_distance + rectangle.width + additional_push;
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