#include "MainGame.h"

#include <iostream>

#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>






MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(61.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {



}



//Public methods

void MainGame::run()
{
	_initSystems();




	_gameloop();

}



//Private methods
void MainGame::_initSystems()
{
	MexEngine::init();

	_window.create("MexEngine", _screenWidth, _screenHeight);

	_initShaders();

	_spriteBatch.init();

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
		_time += 0.01f;

		_camera.update();

		_drawGame();

		_calculateFPS();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 60)
		{
			std::cout << _fps << " FPS" << std::endl;
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


	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt) == true)
	{
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:

			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
				break;

			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;

			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;

			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;

			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE_SPEED);
				break;

			case SDLK_e:
				_camera.setScale(_camera.getScale() - SCALE_SPEED);
				break;
			}

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

	//Set the constantly changing time variable
	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();


	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static MexEngine::GLTexture texture = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	MexEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;


	for (size_t i = 0; i < 1000; i++)
	{
		_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
		_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
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