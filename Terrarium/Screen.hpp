#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace terr {

	class Screen
	{
	public:
		Screen();
		~Screen();

		void draw(sf::RenderWindow&);
		void update();

	protected:
		std::string m_name;
		sf::Font m_font;
	};

}