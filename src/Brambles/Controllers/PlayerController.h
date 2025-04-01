
#include "../Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
	/**
	 * @brief Controls the player movement and interactions.
	 */
    struct PlayerController : public Component
    {
        /** Initializes the player controller. */
        void onInitialize()
        {
            yaw = 0.0f; // Default yaw to face along the negative Z axis
            pitch = 0.0f; // Default pitch
            sensitivity = 0.1f;
        };

        /** Updates the player's state each frame. */
        void onTick();

        /** Handles the player's GUI interactions. */
        //void onGui();

        /** Handles player keyboard input. */
        void handleKeyboardInput();

		void handleMouseInput();



    private:
        glm::vec3 playerStart; ///< Starting position of the player.
        float movementSpeed = 30.0f; ///< Speed at which the player moves.

        float yaw, pitch; ///< Yaw and pitch angles for the camera's orientation.
        float sensitivity; ///< Sensitivity for mouse input.
        float jumpForce = 3.0f; ///< Force applied to the player when jumping.
		float airResistance = 0.3f; ///< Air resistance applied to the player.
		float floorFriction = 0.3f; ///< Friction applied to the player when on the ground.

		bool isGrounded = true; ///< Flag indicating if the player is jumping.
    };
}
