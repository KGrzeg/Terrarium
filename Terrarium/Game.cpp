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
		if (!m_default_font.loadFromFile("arial.ttf"))
		{
			throw "Nie mo¿na wczytaæ czcionki arial.ttf";
		}

		m_start_screen = std::make_unique<Screen>(Screen(m_default_font));
		m_current_screen = m_start_screen.get();
	}
	Game::~Game() {}

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
		m_window.clear(sf::Color::Green);

		if (m_current_screen != nullptr)
		{
			m_current_screen->draw(m_window);
		}
		
		m_window.display();
	}

	void Game::quit()
	{
		m_window.close();
	}

	sf::Font Game::getDefaultFont() const { return m_default_font; }
	sf::RenderWindow& Game::getWindow() { return m_window; }
}
