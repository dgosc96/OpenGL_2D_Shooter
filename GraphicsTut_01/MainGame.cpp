#include "MainGame.h"

#include <iostream>

#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>






MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() 
{
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

	_fpsLimiter.init(_maxFPS);

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
		_fpsLimiter.begin();

		_processInput();
		_time += 0.01f;

		_camera.update();

		_drawGame();

		_fps = _fpsLimiter.end();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 10000)
		{
			std::cout <<(int)_fps << " FPS" << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::_processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 5.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt) == true)
	{
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;

			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
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


	for (size_t i = 0; i < 1; i++)
	{
		_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
		//_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
}

