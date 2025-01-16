
#include <vector>
#include <glm/glm.hpp>

namespace Brambles
{

	/**
	 * @brief Handles user input like mouse movements and key states.
	 */
    struct Input
    {
    public:
        /** Updates mouse position. */
        void onMouseMove(float x, float y);

        /** Sets mouse position. */
        void setMousePosition(float& x, float& y);

        /** Gets mouse position. */
        void getMousePosition(float& dx, float& dy);

        /** Checks if a key is pressed. */
        void isKeyPressed(int key);

        /** Checks if a key is released. */
        void isKeyReleased(int key);

        /** Checks if a key is held down. */
        bool isKey(int key);

        std::vector<int> keys; ///< List of pressed keys.
        std::vector<int> keysPressed; ///< List of recently pressed keys.
        std::vector<int> keysReleased; ///< List of released keys.

        float lastMouseX = 0; ///< Last mouse x position.
        float lastMouseY = 0; ///< Last mouse y position.
        float mouseX = 0; ///< Current mouse x position.
        float mouseY = 0; ///< Current mouse y position.
        bool firstMouse = true; ///< Flag for first mouse movement.

    private:
    };
}
