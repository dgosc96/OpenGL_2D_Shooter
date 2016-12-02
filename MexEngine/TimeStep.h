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

		float getDeltaTime() { return m_deltaTime; }

	private:

		float m_prevTicks;
		float m_totalDeltaTime;
		float m_deltaTime;



		size_t m_iterator = 0;
	};


	class TimeStep
	{
	public:

		static SemiFixedDelta SF_Delta;

	};



}


