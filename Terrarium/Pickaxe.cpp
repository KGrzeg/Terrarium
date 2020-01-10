#include "Pickaxe.hpp"
#include "Utils.hpp"

namespace terr {
	Pickaxe::Pickaxe(GlobalReference global, World* world, Character* player) {
		this->global = global;
		this->world = world;
		this->player = player;
	}

	int Pickaxe::feedEvent(sf::Event& event) {
		if (event.type == sf::Event::EventType::MouseButtonPressed) {
			sf::Vector2i mouse_pos_window = sf::Mouse::getPosition(global->window);
			sf::Vector2f worldPos = global->window.mapPixelToCoords(mouse_pos_window);

			auto player_center = player->getPosition();
			player_center.x += player->getSprite()->getGlobalBounds().width / 2;
			player_center.y += player->getSprite()->getGlobalBounds().height / 2;

			if (Utils::distance(player_center, worldPos) <= range)
				return world->dig(worldPos.x, worldPos.y, power);
		}
		return 0;
	}
}