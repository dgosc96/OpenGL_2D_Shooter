#include "ResourceManager.h"

namespace MexEngine
{
	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}

	TextureCache ResourceManager::_textureCache;
}