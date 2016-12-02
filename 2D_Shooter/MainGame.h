#pragma once
#include <vector>
#include <random>

#include <SDL/SDL.h>
#include <GL/glew.h>


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
#include "HUD.h"


#include "Level.h"


enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	void updateUnits();

private:
	void initSystems();
	void initShaders();
	void gameloop();
	void processInput();
	void drawGame();

	void drawUnits();






	void spawnHumans(const std::vector<std::string>& leveldata, size_t amount);



	MexEngine::Window m_window;
	
	Crosshair m_crosshair;
	HUD		  m_HUD;


	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;



	MexEngine::GLSLProgram	m_colorProgram;
	MexEngine::Camera2D		m_camera;

	MexEngine::SpriteBatch	m_spriteBatch;

	MexEngine::InputManager m_inputManager;
	MexEngine::FpsLimiter	m_fpsLimiter;




	Player*				m_player;
	std::vector<Unit*>  m_enemies;
	std::vector<Unit*>  m_humans;


	int					m_currLvl;
	std::vector<Level*>	m_level;

	float				m_maxFPS;
	float				m_fps;



	
};

