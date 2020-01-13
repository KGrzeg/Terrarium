#include "Character.hpp"
#include <iostream>

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
		{ 7, 11, 24, 19, 12, 29 },
		{ 44, 13, 26, 17, 50, 29 },
		{ 83, 12, 24, 18, 88, 29 },
		{ 121, 11, 24, 19, 126, 29 },
		{ 159, 10, 24, 20, 164, 29 },
		{ 6,43,26,19,-1,-1 },
		{ 43,42,27,19,-1,-1 },
		{ 82,43,26,19,-1,-1 },
		{ 121,45,24,18,-1,-1 },
		{ 160,44,22,19,-1,-1 },
		{ 199,43,20,19,-1,-1 },
		{ 236,43,22,19,-1,-1 },
		{ 273,45,24,18,-1,-1 },
		{ 7,75,24,19,-1,-1 },
		{ 48,68,13,23,-1,-1 },
		{ 85,67,14,24,-1,-1 },
		{ 123,68,23,22,-1,-1 },
		{ 162,76,19,21,-1,-1 },
		{ 200,76,17,21,-1,-1 },
		{ 236,77,22,17,-1,-1 },
		{ 7,171,24,19,-1,-1 },
		{ 44,170,26,19,-1,-1 },
		{ 81,166,26,19,-1,-1 },
		{ 120,165,26,20,-1,-1 },
		{ 159,173,24,17,-1,-1 },
		{ 8,235,24,19,-1,-1 },
		{ 45,236,26,18,-1,-1 },
		{ 83,237,26,17,-1,-1 },
		{ 121,238,26,16,-1,-1 },
		{ 159,241,26,13,-1,-1 },
		{ 198,241,27,13,-1,-1 },
		{ 236,242,29,13,-1,-1 },
		{ 2,267,24,19,-1,-1 },
		{ 39,269,26,17,-1,-1 },
		{ 78,268,24,18,-1,-1 },
		{ 116,267,24,19,-1,-1 },
		{ 154,266,24,20,-1,-1 },
		{ 1,299,26,19,-1,-1 },
		{ 39,298,27,19,-1,-1 },
		{ 77,299,26,19,-1,-1 },
		{ 116,301,24,18,-1,-1 },
		{ 155,300,22,19,-1,-1 },
		{ 194,300,20,19,-1,-1 },
		{ 231,300,22,19,-1,-1 },
		{ 268,301,24,18,-1,-1 },
		{ 2,331,24,19,-1,-1 },
		{ 48,324,13,23,-1,-1 },
		{ 86,323,14,24,-1,-1 },
		{ 115,324,23,22,-1,-1 },
		{ 156,332,19,21,-1,-1 },
		{ 196,333,17,21,-1,-1 },
		{ 231,334,22,17,-1,-1 },
		{ 2,427,24,19,-1,-1 },
		{ 39,426,26,19,-1,-1 },
		{ 78,422,26,19,-1,-1 },
		{ 115,421,26,20,-1,-1 },
		{ 154,429,24,17,-1,-1 },
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
		if (!god_mode)
			handle_gravity(time);
		handle_velocity(time);

		handle_moving(time);

		if (camera_follow) {
			view.setCenter(getPosition().x, getPosition().y);
			global->window.setView(view);
		}
		update_animation(time);
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
		if (test_collision(SIDE_DOWN)) {
			//if falling
			if (velocity.y > 0) velocity.y = 0;
			on_ground = true;
		}
		else
		{
			//add gravity pull to down
			velocity.y += world->getGravity() * time.asSeconds();
			on_ground = false;
		}
	}

	void Character::handle_velocity(sf::Time& time) {
		if (velocity.y < 0 && test_collision(SIDE_TOP)) {
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