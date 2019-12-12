#include "Label.hpp"



namespace terr {
	Label::Label(GlobalReference global, sf::String text)
		: UIElement(global)
	{
		label.setFont(global->assets.getFont("default"));
		label.setString(text);
		label.setFillColor(default_color);
	}
	Label::Label(GlobalReference global, sf::String text, float x, float y)
		: Label(global, text)
	{
		label.setPosition(x, y);
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(label);
	}
	void Label::setPosition(float x, float y)
	{
		label.setPosition(x, y);
	}
}
