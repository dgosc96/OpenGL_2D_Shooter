#pragma once
#include <MexEngine/SpriteBatch.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
class Crosshair
{
public:
	Crosshair(glm::vec2 size, float depth, float radius, std::string texturePath);
	~Crosshair();

	void update(glm::vec2 mousePos, glm::vec2 playerPos);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	glm::vec2 getCenterPosition() { return _position + (_size / 2.0f); }

private:

	glm::vec2			_position;
	glm::vec2			_size;

	float				_depth;
	float				_radius;


	GLint				_textureID;
	MexEngine::Color	_color;

};

