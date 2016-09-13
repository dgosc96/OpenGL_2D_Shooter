#include "Errors.h"

#include <SDL\SDL.h>

#include <iostream>
#include <conio.h>

namespace MexEngine
{
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		_getch();
		SDL_Quit();
		exit(666);
	}
}