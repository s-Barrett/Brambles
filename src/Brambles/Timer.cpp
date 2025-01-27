#include <chrono>
#include <iostream>
#include "Timer.h"

namespace Brambles
{
    // Helper function to get the current time in seconds
    static float getCurrentTime()
    {
        using namespace std::chrono;
        return duration_cast<duration<float>>(high_resolution_clock::now().time_since_epoch()).count();
    }

    Timer::Timer()
    {
        m_startTime = 0.0f;
        m_stopTime = 0.0f;
        m_pausedTime = 0.0f;
        m_lastFrameTime = 0.0f;
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
            m_startTime = getCurrentTime();
            m_lastFrameTime = m_startTime; // Initialize m_lastFrameTime
        }
    }

    void Timer::stop()
    {
        if (!m_stopped)
        {
            m_stopped = true;
            m_stopTime = getCurrentTime();
        }
    }

    void Timer::reset()
    {
        m_startTime = 0.0f;
        m_stopTime = 0.0f;
        m_pausedTime = 0.0f;
        m_lastFrameTime = 0.0f;
        m_paused = false;
        m_stopped = true;
    }

    void Timer::update()
    {
        if (!m_stopped)
        {
            if (m_paused)
            {
                m_pausedTime = getCurrentTime();
            }
        }
    }

    float Timer::getTime()
    {
        if (m_stopped)
        {
            return m_stopTime - m_startTime;
        }
        else
        {
            if (m_paused)
            {
                return m_pausedTime - m_startTime;
            }
            else
            {
                return getCurrentTime() - m_startTime;
            }
        }
    }

    float Timer::getDeltaTime()
    {
        static float previousDeltaTime = 0.016f; // 60fps
        float currentTime = getCurrentTime();
        float deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        // Ensure deltaTime is not too small
        const float minDeltaTime = 0.001f; // Adjust as needed
        if (deltaTime < minDeltaTime)
        {
            deltaTime = minDeltaTime;
        }

        // Debug output
        std::cout << "Current Time: " << currentTime << std::endl;
        std::cout << "Last Frame Time: " << m_lastFrameTime << std::endl;
        std::cout << "Raw Delta Time: " << deltaTime << std::endl;

        // Smoothing
        deltaTime = 0.9f * previousDeltaTime + 0.1f * deltaTime;
        previousDeltaTime = deltaTime;

        return deltaTime;
    }
}