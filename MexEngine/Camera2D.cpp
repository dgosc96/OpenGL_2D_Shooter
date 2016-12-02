#include "Camera2D.h"

namespace MexEngine
{

	Camera2D::Camera2D() :
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_needsMartixUpdate(true),
		m_screenWidth(500),
		m_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{


	}


	void Camera2D::init(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
	}

	void Camera2D::update()
	{
		if (m_needsMartixUpdate)
		{	
		
			glm::vec3 camTranslate(-m_position.x + (m_screenWidth / 2), -m_position.y + (m_screenHeight / 2), 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, camTranslate);


			glm::vec3 scale(m_scale, abs(m_scale), 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;


			m_needsMartixUpdate = false;

		}

	}

	bool Camera2D::isBoxInView(glm::vec2& boxPos, glm::vec2& boxSize)
	{
		glm::vec2 boxRadiusVec = boxSize / 2.0f;

		glm::vec2 scaledScreenDims = glm::vec2(m_screenWidth, m_screenHeight) / m_scale;

		glm::vec2 minDistVec = boxRadiusVec + ( scaledScreenDims / 2.0f);

		glm::vec2 boxCenterPos = boxPos + boxRadiusVec;

		glm::vec2 distVec = boxCenterPos - m_position;


		glm::vec2 collisionDepth = minDistVec - abs(distVec);

		if (collisionDepth.x > 0.0f && collisionDepth.y > 0.0f)
		{
			return true;
		}

		return false;
		
	}


	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		
		screenCoords.y = m_screenHeight - screenCoords.y;

		
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		

		screenCoords /= m_scale;


		screenCoords += m_position;

		return screenCoords;

	}

	glm::vec2 Camera2D::convertWorldToScreen(glm::vec2 worldCoords)
	{
		worldCoords -= m_position;

		worldCoords *= m_scale;

		worldCoords += glm::vec2(m_screenWidth / 2, m_screenHeight / 2);

		worldCoords.y += m_screenHeight;

		return worldCoords;
	}

}