#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.hpp"

namespace terr {
	class Button :
		public UIElement
	{
	public:
		Button(GlobalReference global, sf::String text);
		Button(GlobalReference global, sf::String text, float x, float y);

		void update(sf::Time time) override;
		void handle_event(sf::Event& event) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool is_clicked() { return clicked; };

		void setPosition(float x, float y);
		sf::Text &get_text() { return label; }

	private:
		sf::Text label;
		const sf::Color default_color = sf::Color::White;
		const sf::Color hover_color = sf::Color::Cyan;
		bool hovered;
		bool clicked;
	};

}

