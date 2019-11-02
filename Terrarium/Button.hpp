#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.hpp"

namespace terr {
	class Button :
		public UIElement
	{
	public:
		Button(sf::Font& font, sf::String text) :
			UIElement(font, text)
		{		}

		void update() override
		{
			auto mpos = sf::Mouse::getPosition();
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

			if (pressed && mouseOver(mpos))
			{
				if (m_onClick != nullptr)
					m_onClick();
			}
		}

		void setOnClick(void(*on_click)()) { m_onClick = on_click; }

	private:
		bool mouseOver(sf::Vector2i pos)
		{
			if (pos.x > m_position.x &&
				pos.x < m_position.x + m_size.x &&
				pos.y > m_position.y &&
				pos.y < m_position.y + m_size.y)
				return true;
			return false;
		}

		void(*m_onClick)();
	};

}
