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
	m_size = size;
	m_depth = depth;
	m_radius = radius;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;
	m_color.a = 100;

}


void Crosshair::update(glm::vec2 mousePos, glm::vec2 playerCenterPos)
{


	glm::vec2 diffVec = mousePos - playerCenterPos;
	float mouseDist = glm::length(diffVec);

	m_position = (playerCenterPos + (glm::normalize(diffVec) * m_radius)) - m_size / 2.0f;

}

void Crosshair::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(posAndSize, uv, m_textureID, m_depth, m_color);



}



