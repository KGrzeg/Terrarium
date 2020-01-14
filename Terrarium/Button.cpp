#include "Button.hpp"

namespace terr
{
	Button::Button(GlobalReference global, sf::String text)
		: UIElement(global)
	{
		label.setFont(global->assets.getFont("fancy"));
		label.setString(text);
		label.setFillColor(default_color);
		hovered = false;
		clicked = false;
	};
	Button::Button(GlobalReference global, sf::String text, float x, float y)
		: Button(global, text)
	{
		label.setPosition(x, y);
	}

	void Button::update(sf::Time time)
	{
		auto mpos = sf::Mouse::getPosition(global->window);

		if (label.getGlobalBounds().contains(mpos.x, mpos.y))
		{
			label.setFillColor(hover_color);
			hovered = true;
		}
		else
		{
			label.setFillColor(default_color);
			hovered = false;
		}
		clicked = false;
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(label);
	}


	void Button::handle_event(sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed && hovered)
		{
			clicked = true;
		}
	}

	void Button::setPosition(float x, float y)
	{
		label.setPosition(x, y);
	}


}