#pragma once
#include "Screen.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Character.hpp"
#include "Pickaxe.hpp"
#include "SimpleAnimatedSprite.hpp"
#include "AnimatedSprite.hpp"

namespace terr {
	class ScreenPlay :
		public terr::Screen
	{
	public:
		ScreenPlay(GlobalReference global, WorldSettings& settings);
		~ScreenPlay();
		void draw(sf::Time time) override;
		void update(sf::Time time) override;
		void handle_input() override;
		void addScore(int score);
		void pause() override;

		Character* getPlayer() { return player; }

	private:
		void draw_ui();

		void setup_sheep(WorldSettings& settings);
		void check_end_conditions();

		const float update_fps = 1.f / 60.f;
		sf::Time update_elapsed_time;
		GlobalReference global;
		World world;
		Character* player;
		Pickaxe* pickaxe;
		sf::RectangleShape top_bar;
		sf::RectangleShape help_image;
		sf::RectangleShape background_image;

		bool display_help = false;
		bool is_lose = false;
		bool is_win = false;

		unsigned score = 0;
		float time_left = 1;

		AnimatedSprite* sheep = nullptr;
		SimpleAnimatedSprite* power_sprite = nullptr;
		SimpleAnimatedSprite* time_sprite = nullptr;
		sf::Text power_label;
		sf::Text score_label;
		sf::Text time_label;
	};
}