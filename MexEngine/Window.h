#pragma once
#include <string>

#include <SDL\SDL.h>
#include <GL\glew.h>

namespace MexEngine
{
	enum WindowFlags 
	{ 
		INVISIBLE = 0x1, 
		FULLSCREEN = 0x2, 
		BORDERLESS = 0x4, 
	};

	class Window
	{
	public:
		Window();
		~Window();

		SDL_DisplayMode getDisplayResolution();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags = 0);

		void swapBuffer();

		void setWindowMode(unsigned int windowMode)	{ _windowMode = windowMode; }

		int getScreenWidth()						{ return _screenWidth; }
		int getScreenHeight()						{ return _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;

		unsigned int _windowMode;
	};
}
