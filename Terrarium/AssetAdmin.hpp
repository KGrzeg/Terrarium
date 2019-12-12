#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace terr{
class AssetAdmin
{
public:
	AssetAdmin();
	~AssetAdmin() {};

	void addTexture(sf::String key, sf::String path);
	void addFont(sf::String key, sf::String path);
	
	sf::Texture &getTexture(sf::String key);
	sf::Font &getFont(sf::String key);
	
private:
	std::map<sf::String, sf::Texture> textures;
	std::map<sf::String, sf::Font> fonts;
};

}
