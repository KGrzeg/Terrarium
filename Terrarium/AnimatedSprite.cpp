#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(AnimationDef* animations, AnimationFrameDef* frames, bool auto_start)
{
	this->animations = animations;
	this->frames = frames;

	if (auto_start) playAnimation(0);
	update_frame_intrect();
}

AnimatedSprite::~AnimatedSprite()
{
	delete animations, frames;
}

void AnimatedSprite::update(sf::Time time)
{
	elapsed_time += time;

	float time_period = frame_period;
	if (getCurrentAnimationDef().override_fps)
		time_period = 1 / getCurrentAnimationDef().override_fps;

	if (elapsed_time.asSeconds() >= time_period) {
		next_frame();
		elapsed_time -= sf::seconds(time_period);
	}
}

void AnimatedSprite::playAnimation(int n, bool restart)
{
	current_animation_id = n;
	if (restart) {
		current_frame_id = animations[current_animation_id].frame_start;
		elapsed_time = elapsed_time.Zero;
		update_frame_intrect();
	}
	active = true;
}

void AnimatedSprite::setTexture(const sf::Texture& texture, bool resetRect)
{
	sf::Sprite::setTexture(texture, resetRect);
	update_frame_intrect();
}

void AnimatedSprite::next_frame()
{
	auto curAnim = getCurrentAnimationDef();
	current_frame_id++;
	if (current_frame_id > curAnim.frame_end) {
		//end of animation
		if (curAnim.play_once) {
			current_animation_id = curAnim.next_animation;
			current_frame_id = animations[current_animation_id].frame_start;
		}
		else {
			current_frame_id = curAnim.frame_start;
		}
	}

	update_frame_intrect();
}

void AnimatedSprite::update_frame_intrect()
{
	auto frame = getCurrentFrameDef();
	setTextureRect({ frame.x, frame.y, frame.width, frame.height });

	setOrigin(frame.width / 2, frame.height);
	/*if (frame.origin_x != -1 && frame.oritin_y != -1)
		setOrigin(frame.origin_x - frame.x, frame.oritin_y - frame.y);*/
}
