#include <chrono>
#include "Component.h"

namespace Brambles
{
    /**
     * @brief Manages time and delta time for frames.
     */
    class Timer : public Component
    {
    public:
        Timer()
            : m_startTime(std::chrono::steady_clock::now()),
              m_stopTime(std::chrono::steady_clock::now()),
              m_lastFrameTime(std::chrono::steady_clock::now()),
              m_pausedTime(std::chrono::duration<float>::zero()),
              m_deltaTime(0.0f),
              m_paused(false),
              m_stopped(true) {} /**< Constructor */

        ~Timer() {} /**< Destructor */

        void start();   /**< Starts the timer */
        void stop();    /**< Stops the timer */
        void reset();   /**< Resets the timer */
        void update();  /**< Updates elapsed time */
        float getTime();        /**< Returns total elapsed time */
        float getDeltaTime();   /**< Returns time between frames */

    private:
        std::chrono::steady_clock::time_point m_startTime; /**< Start time */
        std::chrono::steady_clock::time_point m_stopTime;  /**< Stop time */
        std::chrono::steady_clock::time_point m_lastFrameTime; /**< Last frame time */
        std::chrono::duration<float> m_pausedTime; /**< Paused time */
        float m_deltaTime; /**< Delta time */
        bool m_paused; /**< Timer paused flag */
        bool m_stopped; /**< Timer stopped flag */
    };
}
