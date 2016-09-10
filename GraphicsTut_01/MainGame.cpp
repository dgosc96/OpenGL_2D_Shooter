#include "MainGame.h"

#include "Errors.h"

#include <iostream>




MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}



//Public:

void MainGame::run() {
	_initSystems();

	_sprite.init(-0.5f, -0.5f, 1.0f, 1.0f);



	_gameloop();

}



//Private:
void MainGame::_initSystems() {
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED, 
SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	_initShaders();

}

void MainGame::_initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.linkShaders();
}


void MainGame::_gameloop() {
	while (_gameState != GameState::EXIT) {
		_processInput();
		_drawGame();

	}
}


void MainGame::_processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt) == true) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				break;

		}
	}
	
}

void MainGame::_drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnableClientState(GL_COLOR_ARRAY);
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex2f(0, 0);
	//glVertex2f(0, 500);
	//glVertex2f(500, 500);
	//glEnd();

	_colorProgram.use();

	_sprite.draw();

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}