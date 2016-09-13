#pragma once

#include <vector>
namespace MexEngine
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);


	};
}
