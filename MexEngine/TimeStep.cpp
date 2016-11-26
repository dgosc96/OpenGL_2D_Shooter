#include "TimeStep.h"
#include <SDL\SDL.h>
#include <algorithm>

namespace MexEngine
{

	SemiFixedDelta::SemiFixedDelta() :
		MAX_PHYSICS_STEPS(6),
		MAX_DELTA_TIME(1.0f)

	{
		_prevTicks = SDL_GetTicks();

	}



	void SemiFixedDelta::calcTDT(const float DESIRED_FRAMETIME)
	{

		float newTicks = SDL_GetTicks();

		float frameTime = newTicks - _prevTicks;

		_prevTicks = newTicks;

		_totalDeltaTime = frameTime / DESIRED_FRAMETIME;
	

	}

	bool SemiFixedDelta::update_begin()
	{
		_deltaTime = std::min(_totalDeltaTime, MAX_DELTA_TIME);


		if (_totalDeltaTime > 0.0f && _iterator < MAX_PHYSICS_STEPS)
		{
			return true;
		}
		_iterator = 0;
		return false;

	}

	void SemiFixedDelta::update_end()
	{
		_totalDeltaTime -= _deltaTime;
		_iterator++;

	}

	SemiFixedDelta TimeStep::SM_Delta;

}
