
#include "../Component.h"
#include <glm/glm.hpp>

namespace Brambles
{

	/**
	 * @brief Manages camera movement and input handling.
	 */
    struct CameraController : public Component
    {
        void onInitialize()
        {
            yaw = 0.0f; // Default yaw to face along the negative Z axis
            pitch = 0.0f; // Default pitch
            sensitivity = 0.1f;
        };

        /** Updates the player's state each frame. */
        void onTick();

        /** Handles player keyboard input. */
        void handleKeyboardInput();

        void handleMouseInput();

    private:
        glm::vec3 playerStart; ///< Starting position of the player.
        float movementSpeed = 60.0f; ///< Speed at which the player moves.

        float yaw, pitch; ///< Yaw and pitch angles for the camera's orientation.
        float sensitivity; ///< Sensitivity for mouse input.
       
    };
}
