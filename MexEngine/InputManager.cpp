#include "InputManager.h"

namespace MexEngine
{

	InputManager::InputManager() :
		_mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}


	void InputManager::update()
	{
		_prevKeyMap = _keyMap;

	}

	void InputManager::pressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;

	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;


	}

	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;

	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}

	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _prevKeyMap.find(keyID);
		if (it != _prevKeyMap.end())
		{
			return it->second;
		}

		return false;
		

	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (isKeyDown(keyID) && !wasKeyDown(keyID))
		{
			return true;
		}

		return false;

	}
}
