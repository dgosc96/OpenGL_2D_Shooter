#pragma once
#include <MexEngine/SpriteBatch.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
class Crosshair
{
public:
	Crosshair();
	~Crosshair();

	void init(glm::vec2 size, float depth, float radius, std::string texturePath);

	void update(glm::vec2 mousePos, glm::vec2 playerCenterPos);

	void draw(MexEngine::SpriteBatch& spriteBatch);

	glm::vec2 getCenterPosition() { return m_position + (m_size / 2.0f); }

private:

	glm::vec2			m_position;
	glm::vec2			m_size;

	float				m_depth;
	float				m_radius;


	GLint				m_textureID;
	MexEngine::ColorRGBA8	m_color;

};

