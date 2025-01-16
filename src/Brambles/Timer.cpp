#include <ctime> 

#include "Timer.h"

namespace Brambles
{


    Timer::Timer()
    {
        m_startTime = 0;
        m_stopTime = 0;
        m_pausedTime = 0;
        m_paused = false;
        m_stopped = true;
    }

    Timer::~Timer() {}

    void Timer::start()
    {
        if (m_stopped)
        {
            m_stopped = false;
            m_paused = false;
            m_startTime = clock();
            m_lastFrameTime = m_startTime; 
        }
    }

    void Timer::stop()
    {
        if (!m_stopped)
        {
            m_stopped = true;
            m_stopTime = clock();
        }
    }

    void Timer::reset()
    {
        m_startTime = 0;
        m_stopTime = 0;
        m_pausedTime = 0;
        m_lastFrameTime = 0; // Reset last frame time
        m_paused = false;
        m_stopped = true;
    }

    void Timer::update()
    {
        if (!m_stopped)
        {
            if (m_paused)
            {
                m_pausedTime = clock();
            }
        }
    }

    float Timer::getTime()
    {
        if (m_stopped)
        {
            return (float)(m_stopTime - m_startTime) / CLOCKS_PER_SEC;
        }
        else
        {
            if (m_paused)
            {
                return (float)(m_pausedTime - m_startTime) / CLOCKS_PER_SEC;
            }
            else
            {
                return (float)(clock() - m_startTime) / CLOCKS_PER_SEC;
            }
        }
    }

    float Timer::getDeltaTime()
    {
        static float previousDeltaTime = 0.016f; // 60fps
        clock_t currentTime = clock();
        float deltaTime = (float)(currentTime - m_lastFrameTime) / CLOCKS_PER_SEC;
        m_lastFrameTime = currentTime;


        deltaTime = 0.9f * previousDeltaTime + 0.1f * deltaTime;
        previousDeltaTime = deltaTime; //Smoothing

        return deltaTime;
    }

}
