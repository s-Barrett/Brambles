#include <chrono>
#include <deque>
#include "Component.h"

#include <chrono>

namespace Brambles
{
    class Timer : public Component
    {
    public:
        void start();
        void update();
        float getDeltaTime() const;

    private:
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_lastFrameTime;
        std::chrono::steady_clock::time_point m_stopTime;

        double m_deltaTime = 0.0f;
        double  m_fixedTimeStep = 1.0f / 240.0f; // Fixed step at 120 FPS
        double  m_accumulator = 0.0f;

        bool m_stopped = true;
    };
}
