#include "Player.h"

#include <SDL\SDL.h>

#include "Utilities.h"

#include <MexEngine\TimeStep.h>

Player::Player(glm::vec4 posAndSize, float speed)
{

	m_color.setColor(128, 50, 100);
	m_position = glm::vec2(posAndSize.x, posAndSize.y);
	m_size = glm::vec2(posAndSize.z, posAndSize.w);
	m_radius = m_size.x / 2.0f;
	m_speed = speed;
	m_depth = 0.0f;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;


	m_health = 400;

}


Player::~Player()
{
}


void Player::init(glm::vec4 posAndSize, float speed)
{
	m_position = glm::vec2(posAndSize.x, posAndSize.y);
	m_size = glm::vec2(posAndSize.z, posAndSize.w);
	m_speed = speed;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;


}

void Player::draw(MexEngine::SpriteBatch& spriteBatch)
{

	for (size_t i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].draw(spriteBatch);
	}
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(posAndSize, uv, m_textureID, m_depth, m_color);



}

bool Player::processInput(MexEngine::InputManager&		inputManager,
	const std::vector<std::string>& levelData,
	glm::vec2&						mouseCoords)
{
	float currTime = (float)SDL_GetTicks() / 1000;

	m_shouldIMove = false;

	if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		static float LastShotTime;

		if (currTime - LastShotTime > 0.07f)
		{

			shoot(mouseCoords, 5.0f);

			LastShotTime = currTime;


		}


	}

	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
	{
		static float LastShotTimeR;


		if (currTime - LastShotTimeR >= getRandomNumb(2.52f, 2.55f))
		{


			for (size_t i = 0; i <= 50; i++)
			{
				shoot(mouseCoords, 30.0f);
			}


			LastShotTimeR = currTime;


		}

	}

	if (inputManager.isKeyDown(SDLK_w))
	{
		m_direction += glm::vec2(0.0f, 1.0f);
		m_shouldIMove = true;
	}

	if (inputManager.isKeyDown(SDLK_s))
	{
		m_direction += glm::vec2(0.0f, -1.0f);
		m_shouldIMove = true;
	}

	if (inputManager.isKeyDown(SDLK_a))
	{
		m_direction += glm::vec2(-1.0f, 0.0f);
		m_shouldIMove = true;
	}

	if (inputManager.isKeyDown(SDLK_d))
	{
		m_direction += glm::vec2(1.0f, 0.0f);
		m_shouldIMove = true;
	}



	



	return m_shouldIMove;
}


void Player::move()
{
	if (m_direction != glm::vec2(0.0f, 0.0f) && m_shouldIMove == true)
	{

		m_direction = glm::normalize(m_direction);

		m_position += (m_direction * m_speed) * MexEngine::TimeStep::SF_Delta.getDeltaTime();

		m_direction = glm::vec2(0.0f, 0.0f);

	}
}

void Player::shoot(glm::vec2& mouseCoords, float spreadRange, float speed, float bulletSize)
{
	float bulletLifeTime = 10.0f;


	glm::vec2 spread(getRandomNumb(-spreadRange, spreadRange), getRandomNumb(-spreadRange, spreadRange));

	glm::vec2 direction(((mouseCoords - (bulletSize / 4.0f)) - (m_position + (m_size / 2.0f - 5.0f)) ) + spread);
	direction = glm::normalize(direction);

	m_bullets.emplace_back(m_position + (m_size / 2.0f - (bulletSize / 2.0f)), direction, speed, bulletLifeTime, glm::vec2(bulletSize));

}


void Player::updateBullets(const std::vector<std::string> &levelData,
	std::vector<Unit*>& enemies,
	std::vector<Unit*>& humans)
{
	for (size_t i = 0; i < m_bullets.size();)
	{
		if (m_bullets[i].update(levelData, enemies, humans) == true)
		{
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
		}
		else
		{
			i++;
		}

	}

}
