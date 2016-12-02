#include "Zombie.h"
#include <MexEngine/ResourceManager.h> 
#include <MexEngine/TimeStep.h>

#include "Utilities.h"
#include <iostream>

#include <SDL/SDL.h>


Zombie::Zombie(glm::vec2 pos, glm::vec2 size, float speed)
{
	m_color.setColor(0, getRandomNumb(100, 128), 0);
	m_position = pos;
	m_size = size;
	m_radius = m_size.x / 2.0f;
	m_speed = speed;
	m_depth = 0.0f;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/other/PNG/circle.png").id;

	m_damage = 40;
	m_health = 250;
	m_attackSpeed = 0.25f;

	m_lastAttackTime = 0.0f;

}


Zombie::~Zombie()
{
}



void Zombie::move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies)
{
	glm::vec2 dest;

	Unit* closestEnemy = nullptr;
	int	  closestEnemyIndex = NULL;
	float closestDist = (float)INT_MAX;

	for (size_t i = 0; i < enemies.size(); i++)
	{
		glm::vec2	distVec = getDistanceVec(enemies[i]);
		float		distance = glm::length(distVec);

		if (distance < closestDist)
		{
			closestEnemy = enemies[i];
			closestEnemyIndex = i;
			closestDist = distance;

		}

	}


	if ((closestDist < 700.0f) && closestEnemy != nullptr)
	{
		dest = getDistanceVec(closestEnemy) * -1.0f;
		m_direction = glm::normalize(dest);
		m_position += ((m_direction * (m_speed * 3.0f)) * MexEngine::TimeStep::SF_Delta.getDeltaTime());

		closestDist = glm::length(getDistanceVec(closestEnemy));

		if (closestDist <= UNIT_WIDTH)
		{
			if (attack(closestEnemy) == true)
			{
				infect(enemies, allies, closestEnemyIndex);

			}
		}

	}
	else
	{
		float currTime = (float)SDL_GetTicks() / 1000.0f;

		if (currTime - m_dirChangingTime > getRandomNumb(3.5f, 5.5f) || currTime < 10.0f)
		{
			dest = glm::vec2(getRandomNumb(-200.0f, 200.0f), getRandomNumb(-200.0f, 200.0f));

			m_dirChangingTime = currTime;
			m_direction = glm::normalize(dest);


		}
		m_position += ((m_direction * m_speed) * MexEngine::TimeStep::SF_Delta.getDeltaTime());
	}


}


void Zombie::infect(std::vector<Unit*>& enemies, std::vector<Unit*>& allies, size_t killedEnemyINDX)
{

	allies.push_back(new Zombie(enemies[killedEnemyINDX]->getPosition(), 
								enemies[killedEnemyINDX]->getSize()));

	delete enemies[killedEnemyINDX];
	enemies[killedEnemyINDX] = nullptr;

	enemies[killedEnemyINDX] = enemies.back();
	enemies.pop_back();

}