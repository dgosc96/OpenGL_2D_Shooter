#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
#include "DEBUG.h"

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

#if DEBUG
			std::cout << "Loaded texture from file!\n";
#endif // DEBUG

			
			return newTexture;
		}
		return mapIterator->second;

	}
}