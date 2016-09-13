#pragma once
#include "GLTexture.h"

#include <string>

namespace MexEngine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}
