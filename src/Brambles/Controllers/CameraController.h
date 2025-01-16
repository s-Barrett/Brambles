
#include "../Component.h"
#include <glm/glm.hpp>

namespace Brambles
{

	/**
	 * @brief Manages camera movement and input handling.
	 */
    struct CameraController : public Component
    {
        /**
         * @brief Initializes the camera controller with default values.
         */
        void onInitialize()
        {
            yaw = -90.0f; // Default yaw to face along the negative Z axis
            pitch = 0.0f; // Default pitch
            sensitivity = 0.1f;
        }

        void onTick();
        void handleMouseInput();
        void handleKeyboardInput();

    private:
        float yaw, pitch; ///< Yaw and pitch angles for the camera's orientation.
        float sensitivity; ///< Sensitivity for mouse input.
        float movementSpeed = 40.0f; ///< Speed at which the camera moves.
    };
}
