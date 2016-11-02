#include "Human.h"
#include "Utilities.h"

#include <MexEngine/ResourceManager.h>

#include <SDL/SDL.h>

Human::Human(glm::vec4 posAndSize, float speed)
{
	_color.setColor(0, 0, 128);
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.z, posAndSize.w);
	_speed = speed;
	_depth = 0.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;
	_direction = glm::vec2(getRandomNumb(-1.0f, 1.0f), getRandomNumb(-1.0f, 1.0f));
}


Human::~Human()
{
}


void Human::move()
{
	float currTime = (float)SDL_GetTicks() / 1000;

	if (currTime - _dirChangingTime > getRandomNumb(0.5f, 6.5f))
	{
		glm::vec2 dest(getRandomNumb(-200.0f, 200.f), getRandomNumb(-200.0f, 200.f));
		_direction = glm::normalize(dest);

		_dirChangingTime = currTime;
	}
	_position = _position + (_direction * _speed);
	

}