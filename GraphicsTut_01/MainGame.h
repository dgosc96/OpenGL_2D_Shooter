#pragma once
#include <vector>
#include <random>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <MexEngine/GLSLProgram.h>
#include <MexEngine/GLTexture.h>
#include <MexEngine/Sprite.h>
#include <MexEngine/Window.h>
#include <MexEngine/MexEngine.h>
#include <MexEngine/Camera2D.h>
#include <MexEngine/InputManager.h>
#include <MexEngine/Timing.h>

#include <MexEngine/SpriteBatch.h>


#include "Player.h"
#include "Enemy.h"

#include "Crosshair.h"


#include "Level.h"


enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:
	void _initSystems();
	void _initShaders();
	void _gameloop();
	void _processInput();
	void _drawGame();

	void _drawUnits();
	void _updateUnits();

	void _spawnHumans(const std::vector<std::string>& leveldata, size_t amount);



	MexEngine::Window _window;
	
	Crosshair _crosshair;


	int _screenWidth;
	int _screenHeight;
	GameState _gameState;



	MexEngine::GLSLProgram	_colorProgram;
	MexEngine::Camera2D		_camera;

	MexEngine::SpriteBatch	_spriteBatch;

	MexEngine::InputManager _inputManager;
	MexEngine::FpsLimiter	_fpsLimiter;




	Player*				_player;
	std::vector<Unit*>  _enemies;
	std::vector<Unit*>  _humans;


	int					_currLvl;
	std::vector<Level*>	_level;

	float				_maxFPS;
	float				_fps;



	
};

