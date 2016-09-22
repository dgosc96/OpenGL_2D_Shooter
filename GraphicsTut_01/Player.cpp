#include "Player.h"



Player::Player() :
	_posAndSize(0.0f, 0.0f, 50.0f, 50.0f),
	_speed(3.0f)
{
}

Player::~Player()
{
}


void Player::init(glm::vec4 posAndSize, float speed)
{
	_posAndSize = posAndSize;
	_speed		= speed;

}

void Player::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static MexEngine::GLTexture texture = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	MexEngine::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	
	spriteBatch.draw(_posAndSize, uv, texture.id, 0.0f, color);

}

void Player::move(glm::vec2 direction)
{
	_posAndSize.x += (direction.x * _speed);
	_posAndSize.y += (direction.y * _speed);

}