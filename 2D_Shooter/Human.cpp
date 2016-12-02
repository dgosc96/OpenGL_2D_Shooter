#include "Human.h"
#include "Utilities.h"

#include <MexEngine/ResourceManager.h>
#include <MexEngine\TimeStep.h>

#include <SDL/SDL.h>

Human::Human(glm::vec4 posAndSize, float speed)
{
	m_color.setColor(0, 0, getRandomNumb(100, 128));
	m_position = glm::vec2(posAndSize.x, posAndSize.y);
	m_size = glm::vec2(posAndSize.z, posAndSize.w);
	m_radius = m_size.x / 2.0f;
	m_speed = speed;
	m_depth = 0.0f;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;
	m_direction = glm::vec2(getRandomNumb(-1.0f, 1.0f), getRandomNumb(-1.0f, 1.0f));

	m_health = 200;
	m_damage = 1;
}


Human::~Human()
{
}


void Human::move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies)
{
	glm::vec2 dest;


	Unit* closestEnemy = nullptr;
	float closestDist = (float)INT_MAX;

	for (size_t i = 0; i < enemies.size(); i++)
	{
		glm::vec2	distVec		= getDistanceVec(enemies[i]);
		float		distance	= glm::length(distVec);

		if (distance < closestDist)
		{
			closestEnemy = enemies[i];
			closestDist = distance;
		}

	}

	if (closestDist < 700.0f && closestEnemy != nullptr)
	{
		dest = getDistanceVec(closestEnemy);
		m_direction = glm::normalize(dest);

		if (closestDist < 100.0f)
		{
			m_direction *= -1.0f;
		}
		m_position = m_position + (m_direction * (m_speed * 2.0f)) * MexEngine::TimeStep::SF_Delta.getDeltaTime();
	}
	else
	{
		float currTime = (float)SDL_GetTicks() / 1000;

		if (currTime - m_dirChangingTime > getRandomNumb(0.5f, 6.5f))
		{
			dest = glm::vec2(getRandomNumb(-200.0f, 200.f), getRandomNumb(-200.0f, 200.f));
			
			m_dirChangingTime = currTime;
			m_direction = glm::normalize(dest);
			
		}
		m_position += ((m_direction * m_speed) * MexEngine::TimeStep::SF_Delta.getDeltaTime());
	}
	

}