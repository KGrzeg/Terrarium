#pragma once
#include <vector>
#include "Screen.hpp"
#include "UIElement.hpp"
#include "Game.hpp"

namespace terr {
	class ScreenMenu : public Screen
	{
	public:
		ScreenMenu(sf::String name) :Screen(name) {	}
		~ScreenMenu() {
			for (std::vector<UIElement*>::size_type i = 0; i < m_elements.size(); ++i)
			{
				delete m_elements[i];
			}
		};

		void setup()
		{
			Screen::setup(fnt);
			m_middle = window.getSize().x / 2;
		}
		void draw(sf::RenderWindow& window) override
		{
			const unsigned int middle_x = window.getSize().x / 2;

			for (std::vector<UIElement*>::size_type i = 0; i < m_elements.size(); ++i)
			{
				window.draw(*m_elements[i]);
			}
		}
		void update() override {}

		UIElement* AddElement(UIElement *elem)
		{
			//TODO: Œrednio podoba mi siê taki zapis liczenia y, warto kiedyœ poprawiæ
			//pozycjonuj po œrodku
			const int H = 40;	//wysokoœæ + margines pozycji w menu
			auto s = elem->getSize();
			int y = m_first_button_offset + m_elements.size() * H;
			elem->setPosition(m_middle - s.x / 2, y);
			m_elements.push_back(elem);

			return elem;
		}

	protected:
		std::vector<UIElement*> m_elements;
		const int m_first_button_offset = 130;
		int m_middle;
	};
}
