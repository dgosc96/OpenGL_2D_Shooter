#include "Window.h"

#include "Errors.h"


namespace MexEngine
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	SDL_DisplayMode Window::getDisplayResolution()
	{

		SDL_DisplayMode current;

		SDL_Init(SDL_INIT_VIDEO);


		for (size_t i = 0; i < SDL_GetNumVideoDisplays(); ++i)
		{

			int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

			if (should_be_zero != 0)
			{

				SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
				fatalError("");
				exit(100);
			}

			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
			return current;

		}
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE || _windowMode & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN || _windowMode & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS || _windowMode & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}


		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		if (_sdlWindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}


		std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));


		glClearColor(0.0f, 0.11f, 0.12f, 1.0f);


		SDL_GL_SetSwapInterval(0);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		return 0;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlWindow);

	}
}