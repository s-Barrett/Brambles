
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include "Component.h"

namespace Brambles
{
    /**
     * @brief Manages time and delta time for frames.
     */
    class Timer : public Component
    {
    public:
        Timer();  /**< Constructor */
        ~Timer(); /**< Destructor */

        void start();   /**< Starts the timer */
        void stop();    /**< Stops the timer */
        void reset();   /**< Resets the timer */
        void update();  /**< Updates elapsed time */
        float getTime();        /**< Returns total elapsed time */
        float getDeltaTime();   /**< Returns time between frames */

    private:
        clock_t m_startTime; /**< Start time */
        clock_t m_stopTime;  /**< Stop time */
        clock_t m_pausedTime; /**< Paused time */
        clock_t m_lastFrameTime; /**< Last frame time */
        bool m_paused; /**< Timer paused flag */
        bool m_stopped; /**< Timer stopped flag */
    };
}
