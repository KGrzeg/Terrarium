#include "ScreenNewGame.hpp"

namespace terr
{
	void ScreenNewGame::draw(sf::RenderWindow & window)
	{
		window.draw(m_background_rectangle);

		window.draw(m_lbl_title);
		window.draw(m_lbl_world_name);
		window.draw(m_lbl_resources_level);

		window.draw(m_ctrl_world_name);
		window.draw(m_ctrl_resources_level);

		window.draw(m_btn_start);
		window.draw(m_btn_back);
	}
	void ScreenNewGame::update(Game *)
	{
	}
	void ScreenNewGame::setup(Game *game)
	{
		Screen::setup(game);
		
		if (!m_background_tex.loadFromFile("images/menu_background.jpg"))
		{
			throw L"Nie mo¿na wczytaæ obrazu images/menu_background.jpg!";
		}

		const float margin_lbl_ctr = 10.f;

		m_background_rectangle.setSize(sf::Vector2f(m_window_size.x, m_window_size.y));
		m_background_rectangle.setPosition(0, 0);
		m_background_rectangle.setTexture(&m_background_tex);

		m_lbl_title.setFont(m_font);
		m_lbl_world_name.setFont(m_font);
		m_lbl_resources_level.setFont(m_font);

		m_ctrl_world_name.setFont(m_font);
		m_ctrl_resources_level.setFont(m_font);

		m_btn_start.setFont(m_font);
		m_btn_back.setFont(m_font);

		m_lbl_title.setFillColor(sf::Color::White);
		m_lbl_title.setCharacterSize(90);
		m_lbl_world_name.setFillColor(sf::Color::White);
		m_lbl_resources_level.setFillColor(sf::Color::White);

		m_ctrl_world_name.setFillColor(sf::Color::White);
		m_ctrl_resources_level.setFillColor(sf::Color::White);

		m_btn_start.setFillColor(sf::Color::White);
		m_btn_back.setFillColor(sf::Color::White);

		m_lbl_title.setString(L"Nowa gra");
		m_lbl_world_name.setString(L"Nazwa œwiata:");
		m_lbl_resources_level.setString(L"Poziom zasobów:");
		m_ctrl_world_name.setString(L"Nowy Œwiat");
		m_ctrl_resources_level.setString(L"3");

		m_btn_start.setString(L"Start");
		m_btn_back.setString(L"Wróæ");

		m_lbl_title.setPosition((m_window_size.x - m_lbl_title.getLocalBounds().width) / 2, 50);
		m_lbl_world_name.setPosition(60, 300);
		m_lbl_resources_level.setPosition(60, 350);

		m_ctrl_world_name.setPosition(m_lbl_world_name.getPosition() + sf::Vector2f(m_lbl_world_name.getLocalBounds().width + margin_lbl_ctr, .0f));
		m_ctrl_resources_level.setPosition(m_lbl_resources_level.getPosition() + sf::Vector2f(m_lbl_resources_level.getLocalBounds().width + margin_lbl_ctr, .0f));

		m_btn_start.setPosition((m_window_size.x - m_btn_start.getLocalBounds().width) / 2, m_window_size.y - 120);
		m_btn_back.setPosition((m_window_size.x - m_btn_back.getLocalBounds().width) / 2, m_window_size.y - 60);
	}
	void ScreenNewGame::handleEvent(sf::Event & e)
	{
	}
}

