#pragma once
#include <SFML/System.hpp>

namespace terr {
	class Utils
	{
	public:
		static sf::Vector2f vec2f(sf::Vector2u v)
		{
			return {static_cast<float>(v.x), static_cast<float>(v.y)};
		}
		static sf::Vector2f vec2f(sf::Vector2i v)
		{
			return {static_cast<float>(v.x), static_cast<float>(v.y)};
		}
	};
}