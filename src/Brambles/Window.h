#pragma once

#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <memory.h>
#include <iostream>

namespace Brambles
{
    struct Core;

    /**
     * @brief Represents a window with OpenGL context.
     */
    struct Window
    {
        Window(int width, int height);  /**< Constructor to initialize window */
        ~Window();  /**< Destructor to clean up resources */

        /**
         * @brief Retrieves window size.
         * @param _width Output width.
         * @param _height Output height.
         */
        void getWindowSize(int& _width, int& _height) { _width; _height; }

        /**
         * @brief Returns window size as glm::ivec2.
         * @return Window size (width, height).
         */
        glm::ivec2 size();


    private:
        friend struct Brambles::Core;

        SDL_Window* m_raw;  /**< Raw SDL window pointer */
        SDL_GLContext m_context;  /**< OpenGL context */

        // Prevent copy and assignment
        Window(const Window& _copy);
        Window& operator=(const Window& _assign);
    };
}
