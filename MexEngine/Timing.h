#pragma once

namespace MexEngine 
{
	class FpsLimiter
	{
	public:
		FpsLimiter();
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		//return fps
		float end();

	private:
		void _calculateFPS();

		float _fps;
		float _maxFPS;
		float _frameTime;

		unsigned int _startTicks;
	};




}