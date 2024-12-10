#include "Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	struct Transform : public Component
	{

		glm::mat4 getModelMatrix();
		glm::vec3 getPosition();
		void setPosition(glm::vec3& position);


	private:
		glm::vec3 mPosition{ 0.0f };
		glm::vec3 mRotation{ 0.0f };
		glm::vec3 mScale{ 0.0f };
	};
}