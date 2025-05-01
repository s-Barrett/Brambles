
#include <thread>
#include <numeric>  // Add this for std::accumulate
#include <limits>   // For std::numeric_limits<float>
#include <iostream>
#include "Timer.h"

namespace Brambles
{


    void Timer::start()
    {
        m_startTime = std::chrono::steady_clock::now();
        m_lastFrameTime = m_startTime;
        m_stopped = false;
    }

    void Timer::update()
    {
        if (m_stopped) return;

        auto currentTime = std::chrono::steady_clock::now();
        m_deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
        m_lastFrameTime = currentTime;

        // Clamp delta time to avoid large jumps
        if (m_deltaTime > 0.1f) m_deltaTime = 0.1f;

        m_frameTimes.push_back(m_deltaTime);
        if (m_frameTimes.size() > m_frameCount)
            m_frameTimes.pop_front();

        // Only log FPS every ~0.5s instead of every frame
        static float timeSinceLastPrint = 0.0f;
        timeSinceLastPrint += m_deltaTime;
        if (timeSinceLastPrint >= 0.5f)
        {
            float avgFrameTime = std::accumulate(m_frameTimes.begin(), m_frameTimes.end(), 0.0f) / m_frameTimes.size();
            float fps = 1.0f / (avgFrameTime + std::numeric_limits<float>::epsilon());
            std::cout << "FPS: " << fps << std::endl;
            timeSinceLastPrint = 0.0f;
        }

        // Fixed timestep logic (reduced rate to 60Hz)
        const float fixedTimeStep = 1.0f / 60.0f;
        m_accumulator += m_deltaTime;

        int maxSteps = 3;  // Limit physics steps per frame
        int steps = 0;
        while (m_accumulator >= fixedTimeStep && steps < maxSteps)
        {
            // Call game update logic here (move to actual update if needed)
            m_accumulator -= fixedTimeStep;
            ++steps;
        }
    }


    float Timer::getDeltaTime() const
    {
        return m_deltaTime;
    }

}