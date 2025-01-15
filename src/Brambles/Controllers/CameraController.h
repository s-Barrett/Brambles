#include "../Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	struct CameraController : public Component
	{
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
		float yaw, pitch;
		float sensitivity;
		float movementSpeed = 40.0f;
	};

}

