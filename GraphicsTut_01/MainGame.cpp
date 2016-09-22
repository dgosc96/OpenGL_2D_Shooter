#include "MainGame.h"

#include <iostream>

#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>

#define DEBUG 0





MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
#if DEBUG 
	_windowMode = MexEngine::WINDOWED;

#else

	SDL_DisplayMode currentDisplay = _window.getDisplayResolution();

	_screenWidth = currentDisplay.w;
	_screenHeight = currentDisplay.h;
	_windowMode = MexEngine::BORDERLESS;

#endif // DEBUG



	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{

	delete _randomEngine;
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

	_window.create("MexEngine", _screenWidth, _screenHeight, _windowMode);

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

		for (size_t i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update() == true)
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}

		}

		_drawGame();

		_fps = _fpsLimiter.end();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 250)
		{
			std::cout << (int)_fps << " FPS" << std::endl;
			frameCounter = 0;
		}

	}
}

void MainGame::_processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 8.5f;
	const float SCALE_SPEED = 1.05f;

	while (SDL_PollEvent(&evnt))
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


			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		_gameState = GameState::EXIT;
	}


	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_player.move(glm::vec2(0.0f, 1.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_player.move(glm::vec2(0.0f, -1.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_player.move(glm::vec2(-1.0f, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_player.move(glm::vec2(1.0f, 0.0f));
	}



	if (_inputManager.isKeyPressed(SDLK_UP))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_DOWN))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_LEFT))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_RIGHT))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}




	if (_inputManager.isKeyPressed(SDLK_PAGEUP))
	{
		_camera.setScale(_camera.getScale() * SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_PAGEDOWN))
	{
		_camera.setScale(_camera.getScale() / SCALE_SPEED);
	}



	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		static float LastShotTime;
	

		if (_time - LastShotTime >= 0.05f)
		{
			std::uniform_int_distribution<int> randShotSpread(-30, 30);

			glm::vec2 spread( randShotSpread(*_randomEngine), randShotSpread(*_randomEngine));


			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);

			//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;

			glm::vec2 playerPosition(_player.getPosition() + 20.0f);
			glm::vec2 direction = mouseCoords - playerPosition + spread;
			direction = glm::normalize(direction);

			_bullets.emplace_back(playerPosition, direction, 10.0f, 350);

			LastShotTime = _time;
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

	_spriteBatch.begin(MexEngine::GlyphSortType::BACK_TO_FRONT);

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}

	//glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	//glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//static MexEngine::GLTexture texture = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	//MexEngine::Color color;
	//color.r = 255;
	//color.g = 255;
	//color.b = 255;
	//color.a = 255;

	//_spriteBatch.draw(pos, uv, texture.id, 1.0f, color);


	_player.draw(_spriteBatch);

	_spriteBatch.end();

	_spriteBatch.renderBatch();


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.swapBuffer();
}

