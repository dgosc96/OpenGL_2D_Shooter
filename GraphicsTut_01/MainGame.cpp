#include "MainGame.h"

#include <iostream>

#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>
#include "Utilities.h"
#include "CONSTANTS.h"

#include "DEBUG.h"





MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_currLvl(0)
{

	SDL_DisplayMode currentDisplay = _window.getDisplayResolution();
#if DEBUG 

#else
	_screenWidth = currentDisplay.w;
	_screenHeight = currentDisplay.h;

	_window.setWindowMode(MexEngine::BORDERLESS);

#endif



	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	for (size_t i = 0; i < _level.size(); i++)
	{
		delete _level[i];
	}
}



void MainGame::run()
{
	_initSystems();

	_gameloop();
}



void MainGame::_initSystems()
{
	MexEngine::init();

	_window.create("2D_Shooter", _screenWidth, _screenHeight);
	_initShaders();

	_spriteBatch.init();

	_fpsLimiter.init(_maxFPS);

	_level.push_back(new Level("Levels/default.lvl"));

	glm::vec2 playerPosition = _level[_currLvl]->getPlayerPos();
	_player.init(glm::vec4(playerPosition, UNIT_WIDTH, UNIT_WIDTH), 8.0f);

	_camera.setPosition(playerPosition + (float)(UNIT_WIDTH / 2));

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

		_time = (float)SDL_GetTicks() / 1000;

		_camera.update();

		_player.updateBullets(_level[_currLvl]->getLevelData());

		_drawGame();

		_fps = _fpsLimiter.end();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 60)
		{
			std::cout << (int)_fps << " FPS" << std::endl;
			frameCounter = 0;
		}

	}
}

void MainGame::_processInput() {
	SDL_Event evnt;
	glm::vec2 mouseCoords = _inputManager.getMouseCoords();
	mouseCoords = _camera.convertScreenToWorld(mouseCoords);


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
		case SDL_MOUSEWHEEL:

			if (evnt.button.x > 0)
			{
				_camera.setScale(_camera.getScale() * (SCALE_SPEED + 0.2f));
			}
			else
			{
				_camera.setScale(_camera.getScale() / (SCALE_SPEED + 0.2f));
			}
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


	bool didPlayerMove = _player.processInput
	(
		_inputManager,
		_level[_currLvl]->getLevelData(),
		mouseCoords
	);

	if (didPlayerMove == true)
	{
		_camera.setPosition(_player.getPosition() + (float)(UNIT_WIDTH / 2));
	}

}



void MainGame::_drawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);



	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin(MexEngine::GlyphSortType::BACK_TO_FRONT);



	_level[_currLvl]->draw();

	_player.draw(_spriteBatch);


	_spriteBatch.end();



	_spriteBatch.renderBatch();



	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();
}

