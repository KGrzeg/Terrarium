#pragma once
#include <SFML/Graphics.hpp>

namespace terr {
	class UIElement :
		public sf::Drawable
	{
	public:
		UIElement(sf::Font& font, sf::String text)
		{
			m_text.setFont(font);
			m_text.setString(text);


			auto s = m_text.getLocalBounds();
			setSize(s.width, s.height);
			setFgColor(sf::Color::White);
			setBgColor(sf::Color::Transparent);
		};

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(m_backgroundRect);
			target.draw(m_text);
		}
		virtual void update() {}

		void setPosition(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
			m_backgroundRect.setPosition(x, y);

			//center text
			float tx = x + m_backgroundRect.getLocalBounds().width / 2 - m_text.getLocalBounds().width / 2;
			float ty = y + m_backgroundRect.getLocalBounds().height / 2 - m_text.getLocalBounds().height / 2;
			m_text.setPosition(tx, ty);
		}
		void setSize(float x, float y)
		{
			m_size.x = x;
			m_size.y = y;
			m_backgroundRect.setSize(m_size);
		}


		void setFgColor(const sf::Color& fg_color)
		{
			m_fgColor = fg_color;
			m_text.setFillColor(fg_color);
		}
		void setBgColor(const sf::Color& bg_color)
		{
			m_bgColor = bg_color;
			m_backgroundRect.setFillColor(bg_color);
		}

		sf::Vector2f getPosition() const { return m_position; }
		sf::Vector2f getSize() const { return m_size; }
		sf::Color getFgColor() const { return m_fgColor; }
		sf::Color getBgColor() const { return m_bgColor; }

	protected:
		sf::RectangleShape m_backgroundRect;
		sf::Text m_text;
		sf::Vector2f m_position;
		sf::Vector2f m_size;
		sf::Color m_fgColor;
		sf::Color m_bgColor;
	};
}