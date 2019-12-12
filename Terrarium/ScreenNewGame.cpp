#include "ScreenNewGame.hpp"

namespace terr
{
	ScreenNewGame::ScreenNewGame(GlobalReference global) :
		global(global)
	{

		const float margin_lbl_ctr = 10.f;
		const auto window_size = global->window.getSize();

		m_background_rectangle.setSize(sf::Vector2f(window_size.x, window_size.y));
		m_background_rectangle.setPosition(0, 0);
		m_background_rectangle.setTexture(&global->assets.getTexture("menu/background"));

		m_lbl_title.setFont(global->assets.getFont("default"));
		m_lbl_world_name.setFont(global->assets.getFont("default"));
		m_lbl_resources_level.setFont(global->assets.getFont("default"));

		m_ctrl_world_name.setFont(global->assets.getFont("default"));
		m_ctrl_resources_level.setFont(global->assets.getFont("default"));

		m_btn_start.setFont(global->assets.getFont("default"));
		m_btn_back.setFont(global->assets.getFont("default"));

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

		m_lbl_title.setPosition((window_size.x - m_lbl_title.getLocalBounds().width) / 2, 50);
		m_lbl_world_name.setPosition(60, 300);
		m_lbl_resources_level.setPosition(60, 350);

		m_ctrl_world_name.setPosition(m_lbl_world_name.getPosition() + sf::Vector2f(m_lbl_world_name.getLocalBounds().width + margin_lbl_ctr, .0f));
		m_ctrl_resources_level.setPosition(m_lbl_resources_level.getPosition() + sf::Vector2f(m_lbl_resources_level.getLocalBounds().width + margin_lbl_ctr, .0f));

		m_btn_start.setPosition((window_size.x - m_btn_start.getLocalBounds().width) / 2, window_size.y - 120);
		m_btn_back.setPosition((window_size.x - m_btn_back.getLocalBounds().width) / 2, window_size.y - 60);
	}

	void ScreenNewGame::draw(sf::Time time)
	{
		global->window.clear();
		global->window.draw(m_background_rectangle);

		global->window.draw(m_lbl_title);
		global->window.draw(m_lbl_world_name);
		global->window.draw(m_lbl_resources_level);

		global->window.draw(m_ctrl_world_name);
		global->window.draw(m_ctrl_resources_level);

		global->window.draw(m_btn_start);
		global->window.draw(m_btn_back);
		global->window.display();
	}
}

