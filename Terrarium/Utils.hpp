#pragma once
#include <SFML/System.hpp>

namespace terr {
	class Utils
	{
	public:
		static sf::Vector2f vec2f(sf::Vector2u v)
		{
			return { static_cast<float>(v.x), static_cast<float>(v.y) };
		}
		static sf::Vector2f vec2f(sf::Vector2i v)
		{
			return { static_cast<float>(v.x), static_cast<float>(v.y) };
		}
		static double distance(float x1, float y1, float x2, float y2) {
			return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
		}
		static double distance(sf::Vector2f v1, sf::Vector2f v2) {
			return distance(v1.x, v1.y, v2.x, v2.y);
		}
		static double distance(sf::Vector2i v1, sf::Vector2i v2) {
			return distance(v1.x, v1.y, v2.x, v2.y);
		}
		//add vectors
		template<typename T> static T vadd(T v1, T v2) {
			return T(v1.x + v2.x, v1.y + v2.y);
		}
		template<typename T> static T vmul(T v1, double n) {
			return T(v1.x * n, v1.y * n);
		}
	};
}