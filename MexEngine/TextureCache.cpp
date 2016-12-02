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
		
		auto mapIterator = m_textureMap.find(texturePath);

	
		if (mapIterator == m_textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		
			m_textureMap.insert(make_pair(texturePath, newTexture));

#if DEBUG
			std::cout << "Loaded texture from file!\n";
#endif // DEBUG

			
			return newTexture;
		}
		return mapIterator->second;

	}
}