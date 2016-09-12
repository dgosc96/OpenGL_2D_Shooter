#include "MainGame.h"

#include "Errors.h"


#include <iostream>




MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_window(nullptr),
	_gameState(GameState::PLAY),
	_maxFPS(61.0f)
{}

MainGame::~MainGame() {
	for (int i = 0; i < _sprites.size(); i++)
	{
		delete _sprites[i];
	}


}



//Public methods

void MainGame::run()
{
	_initSystems();

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	for (int i = 0; i < 1; i++)
	{
		_sprites.push_back(new Sprite());
		_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	}


	_gameloop();

}



//Private methods
void MainGame::_initSystems()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

	//Check the OpenGL ver.
	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	//Background color
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//Set VSYNC
	SDL_GL_SetSwapInterval(0);

	_initShaders();

}

void MainGame::_initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::_gameloop() {
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();

		_processInput();
		_time += 0.1f;

		_drawGame();

		_calculateFPS();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 60)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}


		float frameTicks = SDL_GetTicks() - startTicks;

		if (1000.0f / _maxFPS > frameTicks && _maxFPS != 0.0f)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
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
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;

		}
	}

}

void MainGame::_drawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);


	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

void MainGame::_calculateFPS()
{
	static const int NUM_SAMPLES = 100;
	static float frametimes[NUM_SAMPLES];
	static int currentFrame = 0;


	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frametimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frametimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 0.0f;
	}


}