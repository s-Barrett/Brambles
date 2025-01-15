#include "../Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	struct PlayerController : public Component
	{
		void onInitialize()
		{


		}
		void onTick();

		void onGui();

		//void handleMouseInput();
		void handleKeyboardInput();



	private:

		glm::vec3 playerStart;

		float movementSpeed = 40.0f;

	};
}