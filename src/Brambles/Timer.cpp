#include <chrono>
#include "Timer.h"

namespace Brambles
{

    void Timer::start()
    {
        if (m_stopped)
        {
            m_startTime = std::chrono::steady_clock::now();
            m_lastFrameTime = m_startTime;
            m_stopped = false;
            m_paused = false;
        }
    }

    void Timer::stop()
    {
        if (!m_stopped)
        {
            m_stopTime = std::chrono::steady_clock::now();
            m_stopped = true;
        }
    }

    void Timer::reset()
    {
        m_startTime = std::chrono::steady_clock::now();
        m_lastFrameTime = m_startTime;
        m_pausedTime = std::chrono::steady_clock::duration::zero();
        m_stopped = false;
        m_paused = false;
    }

    void Timer::update()
    {
        if (m_stopped)
            return;

        auto currentTime = std::chrono::steady_clock::now();
        m_deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
        m_lastFrameTime = currentTime;
    }

    float Timer::getTime()
    {
        if (m_stopped)
        {
            return std::chrono::duration<float>(m_stopTime - m_startTime).count();
        }
        else
        {
            return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_startTime).count();
        }
    }

    float Timer::getDeltaTime()
    {
        return m_deltaTime;
    }
}
