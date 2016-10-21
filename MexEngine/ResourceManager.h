#pragma once
#include <string>

#include "TextureCache.h"

namespace MexEngine
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string &texturePath);

	private:
		static TextureCache _textureCache;
	};
}
