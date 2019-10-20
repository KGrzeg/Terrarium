#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace terr {

	Game::Game()
		:m_window(sf::VideoMode(this->window_width, this->window_height),
			this->name + " v" + this->version,
			sf::Style::Titlebar | sf::Style::Close)
	{
		m_window.setVerticalSyncEnabled(true);
			
		m_current_screen = &m_main_screen;
	}
	Game::~Game() {	}

	void Game::start()
	{
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->quit();
			}

			this->draw();
		}
	}

	void Game::update()
	{
	}

	void Game::draw()
	{
		m_window.clear(sf::Color::Black);

		m_main_screen.draw(m_window);
		
		/*if (m_current_screen != nullptr)
		{
			m_current_screen->draw(m_window);
		}*/

		m_window.display();
	}

	void Game::quit()
	{
		m_window.close();
	}

	sf::RenderWindow& Game::getWindow() { return m_window; }
}
