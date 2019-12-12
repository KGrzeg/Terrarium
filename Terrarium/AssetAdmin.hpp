#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace terr{
class AssetAdmin
{
public:
	AssetAdmin();
	~AssetAdmin() {};

	void addTexture(std::string key, std::string path);
	void addFont(std::string key, std::string path);
	
	sf::Texture &getTexture(std::string key);
	sf::Font &getFont(std::string key);
	
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
};

}
