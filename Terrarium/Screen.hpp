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
		virtual void draw(sf::RenderWindow&) = 0;
		virtual void update() = 0;

	protected:
		std::string m_name;
		sf::Font m_font;
	};

}