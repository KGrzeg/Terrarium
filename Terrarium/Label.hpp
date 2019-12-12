#pragma once
#include "UIElement.hpp"

namespace terr {
	class Label : public UIElement
	{
	public:
		Label(GlobalReference global, sf::String text);
		Label(GlobalReference global, sf::String text, float x, float y);

		void update(sf::Time time) override {};
		void handle_event(sf::Event& event) override {};
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setPosition(float x, float y);
		sf::Text &get_text() { return label; }

	private:
		sf::Text label;
		const sf::Color default_color = sf::Color::White;
	};


}