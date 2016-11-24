#include "Player.h"

#include <SDL\SDL.h>

#include "Utilities.h"

Player::Player(glm::vec4 posAndSize, float speed)
{

	_color.setColor(128, 50, 100);
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.z, posAndSize.w);
	_radius = _size.x / 2.0f;
	_speed = speed;
	_depth = 0.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;


	_health = 400;

}


Player::~Player()
{
}


void Player::init(glm::vec4 posAndSize, float speed)
{
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.z, posAndSize.w);
	_speed = speed;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;


}

void Player::draw(MexEngine::SpriteBatch& spriteBatch)
{

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(spriteBatch);
	}
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);

	spriteBatch.draw(posAndSize, uv, _textureID, _depth, _color);



}

bool Player::processInput(MexEngine::InputManager&		inputManager,
	const std::vector<std::string>& levelData,
	glm::vec2&						mouseCoords)
{
	bool didPlayerMove = false;
	float currTime = (float)SDL_GetTicks() / 1000;



	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		static float LastShotTime;

		if (currTime - LastShotTime >= getRandomNumb(0.01f, 0.15f))
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


			for (size_t i = 0; i <= 100; i++)
			{
				shoot(mouseCoords, 30.0f);
			}


			LastShotTimeR = currTime;


		}
		inputManager.releaseKey(SDL_BUTTON_RIGHT);

	}

	glm::vec2 direction(0.0f, 0.0f);

	if (inputManager.isKeyPressed(SDLK_w))
	{
		direction += glm::vec2(0.0f, 1.0f);
		didPlayerMove = true;
	}

	if (inputManager.isKeyPressed(SDLK_s))
	{
		direction += glm::vec2(0.0f, -1.0f);
		didPlayerMove = true;
	}

	if (inputManager.isKeyPressed(SDLK_a))
	{
		direction += glm::vec2(-1.0f, 0.0f);
		didPlayerMove = true;
	}

	if (inputManager.isKeyPressed(SDLK_d))
	{
		direction += glm::vec2(1.0f, 0.0f);
		didPlayerMove = true;
	}

	if (didPlayerMove == true)
	{
		move(direction);
	}



	return didPlayerMove;
}


void Player::move(glm::vec2 direction)
{
	if (direction != glm::vec2(0.0f, 0.0f))
	{

		direction = glm::normalize(direction);

		_position.x += (direction.x * _speed);
		_position.y += (direction.y * _speed);

		direction = glm::vec2(0.0f, 0.0f);
	}
}

void Player::shoot(glm::vec2& mouseCoords, float spreadRange, float speed, float bulletSize)
{
	int bulletLifeTime = 350;


	glm::vec2 spread(getRandomNumb(-spreadRange, spreadRange), getRandomNumb(-spreadRange, spreadRange));

	glm::vec2 direction(mouseCoords - (_position + (_size / 2.0f - 5.0f)) + spread);
	direction = glm::normalize(direction);

	_bullets.emplace_back(_position + (_size / 2.0f - (bulletSize / 2.0f)), direction, speed, bulletLifeTime, glm::vec2(bulletSize));

}


void Player::updateBullets(const std::vector<std::string> &levelData,
	std::vector<Unit*>& enemies,
	std::vector<Unit*>& humans)
{
	for (size_t i = 0; i < _bullets.size();)
	{
		if (_bullets[i].update(levelData, enemies, humans) == true)
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			i++;
		}

	}

}
