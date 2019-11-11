#include "ScreenMenu.hpp"
#include "Game.hpp"

void terr::ScreenMenu::draw(sf::RenderWindow& window)
{
	window.draw(m_background_shape);
	for (auto const &position : m_positions)
	{
		window.draw(position);
	}
}

void terr::ScreenMenu::update(Game *game)
{
	const auto mouse_pos = sf::Mouse::getPosition(*game->getWindowPtr());

	int i = 0;
	m_hover_on_something = false;
	for (auto &position : m_positions)
	{
		auto bounds = position.getGlobalBounds();

		if (bounds.contains(mouse_pos.x, mouse_pos.y))
		{
			position.setFillColor(m_hover_color);
			m_selected = i;
			m_hover_on_something = true;
		}
		else
		{
			position.setFillColor(m_default_color);
		}
		++i;
	}
}

void terr::ScreenMenu::setup(Game* game, sf::Texture &tex)
{
	Screen::setup(game);
	m_background_texture = tex;
	m_background_shape.setTexture(&m_background_texture);
	m_background_shape.setSize(sf::Vector2f(m_window_size));
}

void terr::ScreenMenu::addPosition(sf::String msg)
{
	auto newpos = sf::Text(msg, m_font, m_menu_font_size);
	newpos.setFillColor(m_default_color);
	const auto x = m_window_size.x / 2 - newpos.getLocalBounds().width / 2;

	newpos.setPosition(x, 0);
	m_positions.push_back(newpos);

	//recalculate Y of entries
	for (std::vector<sf::Font>::size_type i = 0; i < m_positions.size(); ++i)
	{
		const auto y = m_window_size.y / (m_positions.size() + 1) * (i + 1) - m_positions[i].getLocalBounds().height / 2;
		m_positions[i].setPosition(m_positions[i].getPosition().x, y);
	}
}

int terr::ScreenMenu::getSelectedPosition()
{
	return m_hover_on_something ? m_selected : -1;
}
