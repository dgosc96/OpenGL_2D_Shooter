#pragma once
#include <vector>

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


enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:
	//Methods
	void _initSystems();
	void _initShaders();
	void _gameloop();
	void _processInput();
	void _drawGame();



	//Variables
	MexEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;



	MexEngine::GLSLProgram _colorProgram;
	MexEngine::Camera2D _camera;

	MexEngine::SpriteBatch _spriteBatch;

	MexEngine::InputManager _inputManager;
	MexEngine::FpsLimiter _fpsLimiter;


	float _maxFPS;
	float _fps;


	float _time;
};

