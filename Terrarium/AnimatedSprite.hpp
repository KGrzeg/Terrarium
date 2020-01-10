#pragma once
#include <SFML/Graphics.hpp>

namespace terr {

	class AnimatedSprite : public sf::Drawable
	{
	public:
		AnimatedSprite(int frame_width,
			int frame_height,
			const sf::Texture& texture);

		void update(sf::Time time);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void move(float x, float y) { sprite.move(x, y); }
		void setPosition(float x, float y) { sprite.setPosition(x, y); }
		void setFPS(float fps) { fps = fps; }
		void setAnimation(int animation) {
			current_animation = animation;
			sprite.setTextureRect(sf::IntRect(
				current_frame * frame_width,
				current_animation * frame_height,
				frame_width,
				frame_height
			));
		}
		void setAnimating(bool animating) { animating = animating; }

		sf::Sprite* getSprite() { return &sprite; }
		sf::Vector2f getPosition() const { return sprite.getPosition(); }
		sf::FloatRect getLocalBounds() const { return sprite.getLocalBounds(); }
		sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
		float getFPS() const { return fps; }
		int getAnimation() const { return current_animation; }
		bool getAnimating() const { return animating; }

	private:
		void increment_frame();

		int frame_width;
		int frame_height;
		int frames;
		int animations;
		int current_animation;
		int current_frame;
		float fps;
		bool animating;
		sf::Sprite sprite;
		sf::Time elapsed_time;
	};

}