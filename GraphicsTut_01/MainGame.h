#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <vector>

#include "GLSLProgram.h"
#include "GLTexture.h"

#include "Sprite.h"


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
	void _calculateFPS();


	//Variables
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;


	std::vector <Sprite*> _sprites;

	GLSLProgram _colorProgram;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};

