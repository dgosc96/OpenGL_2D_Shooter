#include "Errors.h"

#include <SDL\SDL.h>

#include <iostream>
#include <conio.h>

#include "DEBUG.h"

namespace MexEngine
{
	void fatalError(std::string errorString) {

#if DEBUG
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		_getch();
#endif 


		SDL_Quit();
		exit(666);
	}
}