#include "Crosshair.h"
#include <MexEngine/ResourceManager.h>
#include <iostream>
#include <MexEngine/Camera2D.h>



Crosshair::Crosshair()
{	
}

Crosshair::~Crosshair()
{
}

void Crosshair::init(glm::vec2 size, float depth, float radius, std::string texturePath) 
{
	_size = size;
	_depth = depth;
	_radius = radius;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;
	_color.a = 100;

}


void Crosshair::update(glm::vec2 mousePos, glm::vec2 playerCenterPos)
{


	glm::vec2 diffVec = mousePos - playerCenterPos;
	float mouseDist = glm::length(diffVec);

	_position = (playerCenterPos + (glm::normalize(diffVec) * _radius)) - _size / 2.0f;

}

void Crosshair::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);

	spriteBatch.draw(posAndSize, uv, _textureID, _depth, _color);



}



