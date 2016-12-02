#include "Bullet.h"
#include <SDL/SDL.h>



#include "Utilities.h"

#include <MexEngine\TimeStep.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, float lifeTime, glm::vec2	size) :
	m_direction	(dir),
	m_lifeTime	(lifeTime)
{
	m_position = pos;
	m_speed = speed;
	m_size = size;
	m_radius = m_size.x / 2.0f;
	m_depth = 1.0f;
	m_textureID = MexEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/Bullet.png").id;

	m_birthTime = SDL_GetTicks() / 1000.0f;

	m_damage = 70;
	m_attackSpeed = 0.0f;
	m_lastAttackTime = 0.0f;

	m_color.r = getRandomNumb(60, 255);
	m_color.g = getRandomNumb(60, 255);
	m_color.b = getRandomNumb(60, 255);
}


Bullet::~Bullet()
{
}




bool Bullet::update(const std::vector<std::string> &leveldata, std::vector<Unit*>& enemies, std::vector<Unit*>& humans)
{

	glm::vec2 newPos = m_position + (m_direction * m_speed) * MexEngine::TimeStep::SF_Delta.getDeltaTime();

	float currTime = SDL_GetTicks() / 1000.0f;

	if (currTime - m_birthTime > m_lifeTime || collideWithUnits(enemies, humans, leveldata) || canIMove(newPos, leveldata) == false)
	{
		return true;
	}

	m_position = newPos;
	return false;


}




bool Bullet::collideWithUnits(std::vector<Unit*>& enemies,
	std::vector<Unit*>& allies, const std::vector<std::string> &levelData)
{

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (this != enemies[i] && enemies[i] != nullptr)
		{
			if (CollideWithUnit(enemies[i], levelData)) {
				
				if (attack(enemies[i]))
				{
					
					delete enemies[i];
					enemies[i] = enemies.back();
					enemies.pop_back();
				}
				
				m_direction *= -1;

				return true;
			}

		}
	}

	for (size_t j = 1; j < allies.size(); j++)
	{
		if (this != allies[j])
		{
			if (CollideWithUnit(allies[j], levelData)) {
				
				m_direction *= -1;

				return true;
			}

		}
	}
	return false;
}

bool Bullet::attack(Unit* target)
{

	bool isTargetDead = false;

		target->takeDMG(m_damage);


		if (target->getHealth() <= 0)
		{

			isTargetDead = true;
		}

	return isTargetDead;

}