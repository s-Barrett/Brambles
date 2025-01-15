#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include "Component.h"

namespace Brambles
{
	class Timer : public Component
	{
	public:
		Timer();
		~Timer();
		void start();
		void stop();
		void reset();
		void update();
		float getTime();
		float getDeltaTime();
	private:
		clock_t m_startTime;
		clock_t m_stopTime;
		clock_t m_pausedTime;
		clock_t m_lastFrameTime;
		bool m_paused;
		bool m_stopped;
	};
}