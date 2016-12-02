#include "TimeStep.h"
#include <SDL\SDL.h>
#include <algorithm>

namespace MexEngine
{

	SemiFixedDelta::SemiFixedDelta() :
		MAX_PHYSICS_STEPS(12),
		MAX_DELTA_TIME(1.0f)

	{
		m_prevTicks = SDL_GetTicks();

	}



	void SemiFixedDelta::calcTDT(const float DESIRED_FRAMETIME)
	{

		float newTicks = SDL_GetTicks();

		float frameTime = newTicks - m_prevTicks;

		m_prevTicks = newTicks;

		m_totalDeltaTime = frameTime / DESIRED_FRAMETIME;
	

	}

	bool SemiFixedDelta::update_begin()
	{
		m_deltaTime = std::min(m_totalDeltaTime, MAX_DELTA_TIME);


		if (m_totalDeltaTime > 0.0f && m_iterator < MAX_PHYSICS_STEPS)
		{
			return true;
		}
		m_iterator = 0;
		return false;

	}

	void SemiFixedDelta::update_end()
	{
		m_totalDeltaTime -= m_deltaTime;
		m_iterator++;

	}

	SemiFixedDelta TimeStep::SF_Delta;

}
