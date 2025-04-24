
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

        // Add current frame time to the deque
        m_frameTimes.push_back(m_deltaTime);

        // Keep only the last m_frameCount frames
        if (m_frameTimes.size() > m_frameCount)
            m_frameTimes.pop_front();

        // Calculate average frame time and FPS
        float avgFrameTime = std::accumulate(m_frameTimes.begin(), m_frameTimes.end(), 0.0f) / m_frameTimes.size();
        float fps = 1.0f / (avgFrameTime + std::numeric_limits<float>::epsilon());
        std::cout << "FPS: " << fps << std::endl;

        // Fixed timestep logic
        const float fixedTimeStep = 1.0f / 240.0f;
        m_accumulator += m_deltaTime;

        while (m_accumulator >= fixedTimeStep)
        {
            // Call game update logic here
            m_accumulator -= fixedTimeStep;
        }
    }

    float Timer::getDeltaTime() const
    {
        return m_deltaTime;
    }

}