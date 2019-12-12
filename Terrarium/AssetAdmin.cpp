#include "AssetAdmin.hpp"

namespace terr {

	AssetAdmin::AssetAdmin()
	{
	}

	sf::Texture &AssetAdmin::getTexture(std::string key)
	{
		return textures.at(key);
	}
	sf::Font &AssetAdmin::getFont(std::string key)
	{
		return fonts.at(key);
	}

	void AssetAdmin::addTexture(std::string key, std::string path)
	{
		if (textures.find(key) == textures.end()) {
			sf::Texture tex;
			if (tex.loadFromFile(path))
				textures[key] = tex;
		}
	}
	void AssetAdmin::addFont(std::string key, std::string path)
	{
		if (fonts.find(key) == fonts.end()) {
			sf::Font font;
			if (font.loadFromFile(path))
				fonts[key] = font;
		}
	}

}