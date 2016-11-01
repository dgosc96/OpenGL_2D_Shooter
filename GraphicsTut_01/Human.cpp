#include "Human.h"
#include <MexEngine/ResourceManager.h>


Human::Human(glm::vec4 posAndSize, float speed)
{
	_color.setColor(0, 0, 128);
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_size = glm::vec2(posAndSize.z, posAndSize.w);
	_speed = speed;
	_depth = 0.0f;
	_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;

}


Human::~Human()
{
}
