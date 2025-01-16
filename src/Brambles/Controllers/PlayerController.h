
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
        void onInitialize() {};

        /** Updates the player's state each frame. */
        void onTick();

        /** Handles the player's GUI interactions. */
        void onGui();

        /** Handles player keyboard input. */
        void handleKeyboardInput();

    private:
        glm::vec3 playerStart; ///< Starting position of the player.
        float movementSpeed = 40.0f; ///< Speed at which the player moves.
    };
}
