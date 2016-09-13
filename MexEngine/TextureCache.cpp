#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace MexEngine
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//lookup the texture and see if it's in the map
		auto mapIterator = _textureMap.find(texturePath);

		//check if it's not in the map
		if (mapIterator == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Loaded texture from file!\n";
			return newTexture;
		}
		std::cout << "Loaded Cached texture!\n";
		return mapIterator->second;

	}
}