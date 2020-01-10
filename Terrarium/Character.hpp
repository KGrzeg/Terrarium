#pragma once
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "AnimatedSprite.hpp"

namespace terr {
	class Character : public sf::Drawable
	{
	public:
		Character(GlobalReference global);
		~Character() {
			delete sprite;
		};


		void update(sf::Time time);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void move(float x, float y) { sprite->move(x, y); }
		void setPosition(float x, float y) { sprite->setPosition(x, y); }

		sf::Vector2f getPosition() const { return sprite->getPosition(); }
		sf::Sprite getSprite() { return sprite->getSprite(); };
		

	private:
		AnimatedSprite *sprite;
		const float speed = 65;
	};
}