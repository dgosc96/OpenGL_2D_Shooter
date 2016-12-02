#include "MainGame.h"
#include <MexEngine\DEBUG.h>

#if DEBUG
#include <iostream>
#endif 



#include <MexEngine/Errors.h>
#include <MexEngine/ResourceManager.h>
#include <MexEngine/TimeStep.h>

#include "Utilities.h"
#include "CONSTANTS.h"




MainGame::MainGame() :
	m_screenWidth(1024),
	m_screenHeight(768),
	m_gameState(GameState::PLAY),
	m_maxFPS(0),
	m_currLvl(0)
{
	SDL_DisplayMode currentDisplay = m_window.getDisplayResolution();

#if DEBUG==0
	m_screenWidth = currentDisplay.w;
	m_screenHeight = currentDisplay.h;

	m_window.setWindowMode(MexEngine::BORDERLESS);
#endif



	m_camera.init(m_screenWidth, m_screenHeight);
}

MainGame::~MainGame()
{

	for (size_t i = 0; i < m_level.size(); i++)
	{
		delete m_level[i];
	}

	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	for (size_t i = 0; i < m_humans.size(); i++)
	{
		delete m_humans[i];
	}
}



void MainGame::run()
{
	initSystems();

	gameloop();
}



void MainGame::initSystems()
{
	MexEngine::init();

	m_window.create("2D_Shooter", m_screenWidth, m_screenHeight);
	initShaders();

	m_spriteBatch.init();

	m_fpsLimiter.init(m_maxFPS);

	m_level.push_back(new Level("Levels/default.lvl", m_enemies));

	glm::vec2 playerPosition = m_level[m_currLvl]->getPlayerPos();

	m_player = new Player(glm::vec4(playerPosition, UNIT_WIDTH, UNIT_WIDTH));

	m_humans.push_back(m_player);

	m_camera.setPosition(playerPosition + (float)(UNIT_WIDTH / 2));
	m_camera.setScale(0.5f);

	spawnHumans(m_level[m_currLvl]->getLevelData(), 600);

	m_crosshair.init(glm::vec2(30.0f), -1.0f, 250.0f, "Textures/other/PNG/circle.png");
	m_HUD.init(m_screenWidth, m_screenHeight);

}

void MainGame::initShaders() {
	m_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}

void MainGame::gameloop() {
	while (m_gameState != GameState::EXIT)
	{
		MexEngine::TimeStep::SF_Delta.calcTDT(DESIRED_FRAMETIME);
		m_fpsLimiter.begin();

		while (MexEngine::TimeStep::SF_Delta.update_begin() == true)
		{
			processInput();
			
	
			updateUnits();

			if (!m_humans.empty())
			{
				if (m_player == m_humans[0])
				{
					m_player->updateBullets(m_level[m_currLvl]->getLevelData(), m_enemies, m_humans);

					m_camera.setPosition(m_player->getPosition() + m_player->getSize() / 2.0f);

					m_crosshair.update(m_camera.convertScreenToWorld(m_inputManager.getMouseCoords()), m_player->getCenterPosition());

				}
				else if (m_player != nullptr)
				{
					m_player = nullptr;
				}
			}
			else if (m_player != nullptr)
			{
				m_player = nullptr;
			}

			m_camera.update();
			MexEngine::TimeStep::SF_Delta.update_end();
		}


		m_inputManager.update();

		drawGame();

		m_fps = m_fpsLimiter.end();

#if DEBUG

		float time = SDL_GetTicks() / 1000.0f;
		static float FPS_writingTimer = 0.0f;

		if (time - FPS_writingTimer > 1.0f)
		{
			std::cout << (int)m_fps << " FPS" << std::endl;

			FPS_writingTimer = time;
		}



#endif 




	}
}

void MainGame::processInput() {
	SDL_Event evnt;
	glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
	mouseCoords = m_camera.convertScreenToWorld(mouseCoords);


	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEWHEEL:

			if (evnt.button.x > 0)
			{
				m_camera.setScale(m_camera.getScale() * (SCALE_SPEED + 0.2f));
			}
			else
			{
				m_camera.setScale(m_camera.getScale() / (SCALE_SPEED + 0.2f));
			}
			break;
		case SDL_MOUSEMOTION:


			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}
	}

	if (m_inputManager.isKeyDown(SDLK_ESCAPE))
	{
		m_gameState = GameState::EXIT;
	}


	if (m_inputManager.isKeyDown(SDLK_UP))
	{
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED * MexEngine::TimeStep::SF_Delta.getDeltaTime()));

	}

	if (m_inputManager.isKeyDown(SDLK_DOWN))
	{
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED * MexEngine::TimeStep::SF_Delta.getDeltaTime()));
	}

	if (m_inputManager.isKeyDown(SDLK_LEFT))
	{
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED * MexEngine::TimeStep::SF_Delta.getDeltaTime(), 0.0f));
	}

	if (m_inputManager.isKeyDown(SDLK_RIGHT))
	{
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED * MexEngine::TimeStep::SF_Delta.getDeltaTime(), 0.0f));
	}




	if (m_inputManager.isKeyDown(SDLK_PAGEUP))
	{
		m_camera.setScale(m_camera.getScale() * SCALE_SPEED);
	}

	if (m_inputManager.isKeyDown(SDLK_PAGEDOWN))
	{
		m_camera.setScale(m_camera.getScale() / SCALE_SPEED);
	}

	if (m_player != nullptr)
	{
		bool didPlayerMove = m_player->processInput
		(
			m_inputManager,
			m_level[m_currLvl]->getLevelData(),
			m_crosshair.getCenterPosition()
		);
	}




}



void MainGame::drawGame() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);



	GLint pLocation = m_colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.begin(MexEngine::GlyphSortType::BACK_TO_FRONT);

	if (m_player != nullptr)
	{
		m_crosshair.draw(m_spriteBatch);
	}

	m_level[m_currLvl]->draw();

	drawUnits();

	

	m_spriteBatch.end();



	m_spriteBatch.renderBatch();
	m_HUD.draw(m_colorProgram);


	glBindTexture(GL_TEXTURE_2D, 0);

	m_colorProgram.unuse();

	m_window.swapBuffer();
}

void MainGame::drawUnits()
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{

		if (m_camera.isBoxInView(m_enemies[i]->getPosition(), m_enemies[i]->getSize()))
		{
			m_enemies[i]->draw(m_spriteBatch);
		}

	}

	for (size_t j = 0; j < m_humans.size(); j++)
	{
		if (m_camera.isBoxInView(m_humans[j]->getPosition(), m_humans[j]->getSize()))
		{
			m_humans[j]->draw(m_spriteBatch);
		}
	}

}



void MainGame::updateUnits()
{
	for (size_t j = 0; j < m_humans.size(); j++)
	{
		m_humans[j]->move(m_enemies, m_humans);
		m_humans[j]->collideWithUnits(m_enemies, m_humans, m_level[m_currLvl]->getLevelData());
		m_humans[j]->collideWithLevel(m_level[m_currLvl]->getLevelData());


	}
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->move(m_humans, m_enemies);
		m_enemies[i]->collideWithUnits(m_enemies, m_humans, m_level[m_currLvl]->getLevelData());
		m_enemies[i]->collideWithLevel(m_level[m_currLvl]->getLevelData());

	}


}





void MainGame::spawnHumans(const std::vector<std::string>& leveldata, size_t amount)
{

	for (size_t i = 0; i < amount;)
	{
		float x = getRandomNumb(1.0f, (leveldata[0].size() - 2) * TILE_WIDTH);
		float y = getRandomNumb(1.0f, (leveldata.size() - 2) * TILE_WIDTH);

		int tileX = (int)(x / TILE_WIDTH);
		int tileY = (int)(y / TILE_WIDTH);

		if (leveldata[tileY][tileX] == '.')
		{

			glm::vec4 posAndSize(x, y, UNIT_WIDTH, UNIT_WIDTH);
			m_humans.push_back(new Human(posAndSize));

			i++;
		}
	}




}