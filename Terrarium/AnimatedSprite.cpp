#include "AnimatedSprite.hpp"


namespace terr {
	AnimatedSprite::AnimatedSprite(int frame_width,
		int frame_height,
		int frames,
		int animations,
		const sf::Texture& texture) :

		frame_width(frame_width),
		frame_height(frame_height),
		frames(frames),
		animations(animations),
		sprite(texture) {

		current_animation = 0;
		current_frame = 0;
		fps = 1 / 16;

		sprite.setTextureRect(sf::IntRect(
			current_frame * frame_width,
			current_animation * frame_height,
			frame_width,
			frame_height
		));
	}

	void AnimatedSprite::update(sf::Time time) {
		elapsed_time += time;

		if (elapsed_time.asSeconds() >= fps) {
			increment_frame();

		}
	}

	void AnimatedSprite::increment_frame() {
		current_frame = (++current_frame) % frames;
		elapsed_time -= sf::seconds(fps);

		sprite.setTextureRect(sf::IntRect(
			current_frame * frame_width,
			current_animation * frame_height,
			frame_width,
			frame_height
		));
	}

	void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
}