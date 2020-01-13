#include "SimpleAnimatedSprite.hpp"


namespace terr {
	SimpleAnimatedSprite::SimpleAnimatedSprite(int frame_width,
		int frame_height,
		const sf::Texture& texture) :

		frame_width(frame_width),
		frame_height(frame_height),
		sprite(texture) {

		frames = texture.getSize().x / frame_width;
		animations = texture.getSize().y / frame_height;
		current_animation = 0;
		current_frame = 0;
		fps = 1.f / 4.f;
		animating = true;

		sprite.setTextureRect(sf::IntRect(
			current_frame * frame_width,
			current_animation * frame_height,
			frame_width,
			frame_height
		));
	}

	void SimpleAnimatedSprite::update(sf::Time time) {
		if (!animating)
			return;

		elapsed_time += time;

		if (elapsed_time.asSeconds() >= fps) {
			increment_frame();
		}
	}

	void SimpleAnimatedSprite::playOnce(int animation)
	{
		back_to_animation = current_animation;
		current_animation = animation;
		elapsed_time = sf::seconds(0);
	}

	void SimpleAnimatedSprite::increment_frame() {
		current_frame = (++current_frame) % frames;
		elapsed_time -= sf::seconds(fps);

		//reset played_once animation
		if (current_frame == 0 && back_to_animation != -1) {
			current_animation = back_to_animation;
			back_to_animation = -1;
		}

		sprite.setTextureRect(sf::IntRect(
			current_frame * frame_width,
			current_animation * frame_height,
			frame_width,
			frame_height
		));
	}

	void SimpleAnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
}