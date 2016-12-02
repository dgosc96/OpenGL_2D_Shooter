#include "Timing.h"

#include <SDL/SDL.h>


namespace MexEngine
{
	FpsLimiter::FpsLimiter()
	{
	}

	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);

	}

	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		m_maxFPS = maxFPS;

	}

	void FpsLimiter::begin()
	{
		m_startTicks = SDL_GetTicks();

	}
	float FpsLimiter::end() 
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - m_startTicks;

		if (1000.0f / m_maxFPS > frameTicks && m_maxFPS != 0.0f)
		{
			SDL_Delay(1000 / m_maxFPS - frameTicks);
		}

		return m_fps;

	}

	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 100;
		static float frametimes[NUM_SAMPLES];
		static int currentFrame = 0;


		static float prevTicks = SDL_GetTicks();

		float currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;
		frametimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;

		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frametimes[i];
		}

		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			m_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			m_fps = 0.0f;
		}


	}
}