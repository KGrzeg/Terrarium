#include "AssetAdmin.hpp"

namespace terr {

	AssetAdmin::AssetAdmin()
	{
	}

	sf::Texture &AssetAdmin::getTexture(sf::String key)
	{
		return textures.at(key);
	}
	sf::Font &AssetAdmin::getFont(sf::String key)
	{
		return fonts.at(key);
	}
	
	void AssetAdmin::addTexture(sf::String key, sf::String path)
	{
		sf::Texture tex;
		tex.loadFromFile(path);

		textures.at(key) = tex;
	}
	void AssetAdmin::addFont(sf::String key, sf::String path)
	{
		sf::Font font;
		font.loadFromFile(path);

		fonts.at(key) = font;
	}
	
}