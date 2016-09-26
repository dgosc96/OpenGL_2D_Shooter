#include "Player.h"

#include "Utilities.h"

Player::Player() :
	_posAndSize(0.0f, 0.0f, 50.0f, 50.0f),
	_position(glm::vec2(_posAndSize.x, _posAndSize.y)),
	_size(glm::vec2(_posAndSize.w, _posAndSize.z)),
	_speed(3.0f)
{

}

Player::~Player()
{
}


void Player::init(glm::vec4 posAndSize, float speed)
{
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.w, posAndSize.z);
	_speed = speed;
	_posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);


}

void Player::draw(MexEngine::SpriteBatch& spriteBatch)
{

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(spriteBatch);
	}
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static MexEngine::GLTexture _texture = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	MexEngine::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(_posAndSize, uv, _texture.id, 0.0f, color);



}

void Player::move(glm::vec2 direction)
{
	glm::vec2 newPosition;
	newPosition.x = _position.x + (direction.x * _speed);
	newPosition.y = _position.y + (direction.y * _speed);

	if (_canIMove(newPosition ))
	{
		_position = newPosition;

		_posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);
	}





}

void Player::shoot(glm::vec2& mouseCoords, float spreadRange, float speed)
{
	glm::vec2 spread(getRandomNumb(-spreadRange, spreadRange), getRandomNumb(-spreadRange, spreadRange));

	glm::vec2 direction(mouseCoords - (_position + 20.0f) + spread);
	direction = glm::normalize(direction);

	_bullets.emplace_back(_posAndSize + 20.0f, direction, speed, 350);
}


void Player::updateBullets()
{
	for (size_t i = 0; i < _bullets.size();)
	{
		if (_bullets[i].update(_leveldata) == true)
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


bool Player::_canIMove(glm::vec2 newPosition)
{	

	int xTileNumb = ((int)newPosition.x + 9) / 50;

	int yTileNumb = ((int)newPosition.y + 9) / 50;


	int yTileNumbU = ((int)newPosition.y + 42) / 50;

	int xTileNumbR = ((int)newPosition.x + 40) / 50;


	if (_leveldata[yTileNumb][xTileNumb] == '#' ||
		_leveldata[yTileNumb][xTileNumbR] == '#' ||
		_leveldata[yTileNumbU][xTileNumb] == '#' ||
		_leveldata[yTileNumbU][xTileNumbR] == '#')
	{
		return false;
	}

	return true;

}