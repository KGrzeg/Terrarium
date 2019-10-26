#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace terr {

	class Screen
	{
	public:
		~Screen() = default;
		Screen(sf::String name)
			:m_name(name)
		{}

		void setup(sf::Font& fnt)
		{
			m_font = fnt;
		}
		void draw(sf::RenderWindow&);
		void update();

	protected:
		std::string m_name;
		sf::Font m_font;
	};

}