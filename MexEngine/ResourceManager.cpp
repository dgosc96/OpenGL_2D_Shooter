#include "ResourceManager.h"

namespace MexEngine
{
	GLTexture ResourceManager::getTexture(const std::string &texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}

	TextureCache ResourceManager:: _textureCache;
}