#pragma once
#include "Screen.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Character.hpp"
#include "Pickaxe.hpp"
#include "SimpleAnimatedSprite.hpp"

namespace terr {
	class ScreenPlay :
		public terr::Screen
	{
	public:
		ScreenPlay(GlobalReference global, WorldSettings settings);
		~ScreenPlay();
		void draw(sf::Time time) override;
		void update(sf::Time time) override;
		void handle_input() override;
		void addScore(int score);
		void pause() override;

		Character* getPlayer() { return player; }

	private:
		void draw_ui();

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

		unsigned score = 0;

		SimpleAnimatedSprite* power_sprite;
		sf::Text power_label;
		sf::Text score_label;
	};
}