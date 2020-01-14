#include "ScreenMenu.hpp"
#include "Utils.hpp"

namespace terr
{
	typedef Utils U;

	ScreenMenu::ScreenMenu(GlobalReference global) :
		global(global)
	{
		m_background_shape.setTexture(&global->assets.getTexture("menu/background"));
		m_background_shape.setSize(U::vec2f(global->window.getSize()));
	}

	void ScreenMenu::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(m_background_shape);
		for (auto const &position : m_positions)
		{
			global->window.draw(position);
		}
		global->window.display();
	}

	void ScreenMenu::update(sf::Time time)
	{
		const auto mouse_pos = sf::Mouse::getPosition(global->window);

		int i = 0;
		m_hover_above = -1;
		for (auto &position : m_positions)
		{
			auto bounds = position.getGlobalBounds();

			if (bounds.contains(mouse_pos.x, mouse_pos.y))
			{
				position.setFillColor(m_hover_color);
				m_hover_above = i;
			}
			else
			{
				position.setFillColor(m_default_color);
			}
			++i;
		}
	}

	void ScreenMenu::addPosition(sf::String msg)
	{
		auto newpos = sf::Text(msg, global->assets.getFont("fancy"), m_menu_font_size);
		newpos.setFillColor(m_default_color);
		const auto window_width = global->window.getSize();
		const auto x = window_width.x / 2 - newpos.getLocalBounds().width / 2;

		newpos.setPosition(x, 0);
		m_positions.push_back(newpos);

		//recalculate Y of entries
		for (std::vector<sf::Font>::size_type i = 0; i < m_positions.size(); ++i)
		{
			const auto y = window_width.y / (m_positions.size() + 1) * (i + 1) - m_positions[i].getLocalBounds().height / 2;
			m_positions[i].setPosition(m_positions[i].getPosition().x, y);
		}
	}

	void ScreenMenu::handle_input()
	{
		sf::Event event;
		while (global->window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && m_hover_above != -1)
			{
				clicked_option(m_hover_above);
			}
		}
	}

}




