#include "../Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	struct PlayerController : public Component
	{
		void onInitialize()
		{
			playerStart = getPosition();

		}
		void onTick();
		//void handleMouseInput();
		void handleKeyboardInput();



	private:
		glm::vec3 playerStart = glm::vec3(0.0f, 0.0f, 0.0f);
		float playerSpeed = 0.2f;

	};
}