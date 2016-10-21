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

	GLTexture TextureCache::getTexture(const std::string &texturePath)
	{
		
		auto mapIterator = _textureMap.find(texturePath);

	
		if (mapIterator == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Loaded texture from file!\n";
			return newTexture;
		}
		return mapIterator->second;

	}
}