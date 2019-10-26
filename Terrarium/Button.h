#pragma once
#include <SFML/Graphics.hpp>

namespace terr {
	class Button : public sf::Drawable
	{
	public:
		Button(sf::String text)
		{
			this->text.setString(text);
			this->text.setColor(m_textColor);
		};
		~Button();

		void setup(sf::Font &font)
		{
			text.setFont(font);
		}

		sf::Text text;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(text, states);
		}

	protected:
		bool highligh = false;
		void(*on_click)(void); //wskaŸnik na funkcjê, która zostanie uruchomiona po naciœniêciu przycisku

		const sf::Color m_textColor = sf::Color(220.0f, 220.0f, 220.0f, 255.0f);
		const sf::Color m_textColorHighligh = sf::Color(255.0f, 255.0f, 255.0f, 255.0f);
	};
}
