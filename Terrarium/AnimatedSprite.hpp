#pragma once
#include <SFML/Graphics.hpp>

typedef struct {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int origin_x = -1;
	int oritin_y = -1;
} AnimationFrameDef;

typedef struct {
	int frame_start = 0;
	int frame_end = 0;
	bool play_once = false;
	int next_animation = 0;
	float override_fps = 0;
} AnimationDef;

class AnimatedSprite :
	public sf::Sprite
{
public:
	AnimatedSprite(AnimationDef* animations, AnimationFrameDef* frames, bool auto_start = true);
	~AnimatedSprite();

	void update(sf::Time time);
	void playAnimation(int n, bool restart = false);

	void setTexture(const sf::Texture& texture, bool resetRect = false);
	void setFPS(float fps) { frame_period = 1.f / fps; }
	void setFramePeriod(float fps) { frame_period = fps; }
	void freeze() { active = false; }
	void unfreeze() { active = true; }

	float getFPS() { return 1.f / frame_period; }
	float getFramePeriod() { return frame_period; }
	int getCurrentAnimation() { return current_animation_id; }
	AnimationFrameDef getCurrentFrameDef() { return frames[current_frame_id]; }
	AnimationDef getCurrentAnimationDef() { return animations[current_animation_id]; }
private:
	void next_frame();
	void update_frame_intrect();

	AnimationDef* animations;
	AnimationFrameDef* frames;
	int current_animation_id = 0;
	int current_frame_id = 0;
	bool active = false;
	float frame_period = 0.2f;

	sf::Time elapsed_time;
};

