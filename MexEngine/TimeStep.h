#pragma once


namespace MexEngine
{

	class SemiFixedDelta
	{
	public:
		SemiFixedDelta();

		const int MAX_PHYSICS_STEPS;
		const float MAX_DELTA_TIME;

		void calcTDT(const float DESIRED_FRAMETIME);

		bool update_begin();
		void update_end();

		float getDeltaTime() { return _deltaTime; }

	private:

		float _prevTicks;
		float _totalDeltaTime;
		float _deltaTime;



		size_t _iterator = 0;
	};


	class TimeStep
	{
	public:

		static SemiFixedDelta SM_Delta;

	};



}


