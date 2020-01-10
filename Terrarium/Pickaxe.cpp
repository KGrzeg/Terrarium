#include "Pickaxe.hpp"


namespace terr {
	Pickaxe::Pickaxe(GlobalReference global, World* world) {
		this->global = global;
		this->world = world;
	}

	int Pickaxe::feedEvent(sf::Event& event) {
		if (event.type == sf::Event::EventType::MouseButtonPressed) {
			//sf::Vector2i mouse_pos_window = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2i mouse_pos_window = sf::Mouse::getPosition(global->window);
			sf::Vector2f worldPos = global->window.mapPixelToCoords(mouse_pos_window);

			return world->dig(worldPos.x, worldPos.y, power);
		}
		return 0;
	}
}