#include "ScreenMenu.hpp"
void terr::ScreenMenu::draw(sf::RenderWindow& window)
{
	for (auto const &position : m_positions)
	{
		window.draw(position);
	}
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
		const auto y = m_window_size.y / (m_positions.size()+1) * (i + 1);
		m_positions[i].setPosition(m_positions[i].getPosition().x, y);
	}
}
