#pragma once
#include <map>

#include "GLTexture.h"


namespace MexEngine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string &texturePath);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};

}