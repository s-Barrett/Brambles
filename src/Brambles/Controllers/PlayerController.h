
#include "../Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
	/**
	 * @brief Controls the player movement and interactions.
	 */
	struct AudioSource;

    struct PlayerController : public Component
    {


        /** Updates the player's state each frame. */
        void onInitialize() override;
        void onTick() override;


        /** Handles the player's GUI interactions. */
        //void onGui();

        /** Handles player keyboard input. */
        void handleKeyboardInput();

		void handleMouseInput();

		void handleFootsteps();



    private:
        glm::vec3 playerStart; ///< Starting position of the player.
        float movementSpeed = 10.0f; ///< Speed at which the player moves.

        float yaw, pitch; ///< Yaw and pitch angles for the camera's orientation.
        float sensitivity; ///< Sensitivity for mouse input.
        float jumpForce = 6.2f; ///< Force applied to the player when jumping.
		

		bool isGrounded = true; ///< Flag indicating if the player is jumping.

        float tiltAngle = 0.0f;        // Current tilt angle
        float maxTiltAngle = 5.0f;     // Maximum tilt angle in degrees
        float tiltSpeed = 10.0f;       // How fast the camera tilts
        float tiltReturnSpeed = 5.0f;   // How fast it returns to center

        std::shared_ptr<AudioSource> footstepAudio;
        float footstepTimer;
        bool isMoving;
    };
}
