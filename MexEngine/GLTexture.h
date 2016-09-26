#pragma once
#include <GL\glew.h>
#include <string>
namespace MexEngine
{
	struct GLTexture {
		GLuint id;
		int width;
		int height;
		std::string filePath;
	};
}