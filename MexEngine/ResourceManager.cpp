#include "ResourceManager.h"

namespace MexEngine
{
	GLTexture ResourceManager::getTexture(const std::string &texturePath)
	{
		return m_textureCache.getTexture(texturePath);
	}

	TextureCache ResourceManager:: m_textureCache;
}