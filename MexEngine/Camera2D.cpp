#include "Camera2D.h"

namespace MexEngine
{

	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(0.75f),
		_needsMartixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{


	}


	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update()
	{
		if (_needsMartixUpdate)
		{	
		
			glm::vec3 camTranslate(-_position.x + (_screenWidth / 2), -_position.y + (_screenHeight / 2), 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, camTranslate);


	


			glm::vec3 scale(_scale, abs(_scale), 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;


			_needsMartixUpdate = false;

		}

	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		
		screenCoords.y = _screenHeight - screenCoords.y;

		
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		

		screenCoords /= _scale;


		screenCoords += _position;

		return screenCoords;

	}


}