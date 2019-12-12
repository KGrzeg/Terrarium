#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "UIElement.hpp"

#define UNSET_KEY "none"

namespace terr {
	typedef std::unique_ptr<UIElement> UIElementReference;
	
	class UIGrid : public sf::Drawable
	{
	public:
		UIGrid() {};
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void update(sf::Time time);
		virtual void handle_event(sf::Event &event);

		void add_element(std::string key, UIElementReference element);
		UIElementReference &get_element(std::string key);
		std::string clicked_button() { return clicked_btn; };

	private:
		std::map<std::string, UIElementReference> elements;
		std::string clicked_btn = UNSET_KEY;
	};

}
