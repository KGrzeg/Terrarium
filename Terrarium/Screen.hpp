#pragma once
#include <SFML/Graphics.hpp>

namespace terr {


	class Screen
	{
	public:

		virtual void setup() = 0;

		virtual void handle_input() = 0;
		virtual void update(sf::Time time) = 0;
		virtual void draw(sf::Time time) = 0;

		virtual void pause() {};
		virtual void reset() {};
	};

	typedef std::unique_ptr<Screen> ScreenReference;
}