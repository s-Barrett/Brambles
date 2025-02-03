
#include <thread>
#include <deque>
#include "Timer.h"

namespace Brambles
{
#include "Timer.h"

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

        const float fixedTimeStep = 1.0f / 240.0f; // 60 FPS target
        m_accumulator += m_deltaTime;

        while (m_accumulator >= fixedTimeStep)
        {
            // Call game update logic here
            m_accumulator -= fixedTimeStep;
        }

        m_deltaTime = fixedTimeStep; // Use fixed timestep for movement calculations


        // Clamp delta time to avoid large jumps
        if (m_deltaTime > 0.1f) m_deltaTime = 0.1f;
    }

    float Timer::getDeltaTime() const
    {
        return m_deltaTime;
    }

}