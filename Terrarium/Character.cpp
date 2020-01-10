#include "Character.hpp"

namespace terr {
	Character::Character(GlobalReference global)
	{
		sprite = new AnimatedSprite(80, 80, global->assets.getTexture("game/character2"));
		sprite->setAnimation(3);
	}

	void Character::update(sf::Time time) {
		sprite->update(time);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			move(-speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move(speed * time.asSeconds(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move(0, -speed * time.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move(0, speed * time.asSeconds());
		}
	}

	void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*sprite);
	}

}