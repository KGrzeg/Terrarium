#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace terr {
	class UIElement : public sf::Drawable
	{
	public:
		UIElement(GlobalReference global) : global(global) {};

		virtual void update(sf::Time time) = 0;
		//void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void handle_event(sf::Event &event) = 0;

	protected:
		GlobalReference global;
	};
}

