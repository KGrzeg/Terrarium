#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace terr {

	class Screen
	{
	public:
		Screen();
		Screen(sf::Font&);
		~Screen();

		void draw(sf::RenderWindow&);
		void update();

		
	private:
		std::string m_name;
		sf::Font m_font;
		sf::Color m_background_color;
	};

}