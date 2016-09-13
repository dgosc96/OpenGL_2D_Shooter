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
	MexEngine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;


	std::vector <MexEngine::Sprite*> _sprites;

	MexEngine::GLSLProgram _colorProgram;
	MexEngine::Camera2D _camera;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};

