#include "Camera2D.h"

namespace MexEngine
{

	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
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
			//Camera Translation
			glm::vec3 translate(-_position.x + (_screenWidth / 2), -_position.y + (_screenHeight / 2), 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);


			//Camera Scale
			//if (_scale < 0)
			//	_scale = 0;

			glm::vec3 scale(_scale, abs(_scale), 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;


			_needsMartixUpdate = false;

		}

	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		//invert Y direction
		screenCoords.y = _screenHeight - screenCoords.y;

		//Make it so that 0 is the center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		
		//Scale the coordinates
		screenCoords /= _scale;

		//Translate with the camera position;
		screenCoords += _position;

		return screenCoords;

	}


}