#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Brambles
{

	glm::mat4 Transform::getModelMatrix()
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, mPosition);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));
		
		return model;
	}

	glm::vec3 Transform::getPosition()
	{
		return mPosition;
	}

	void Transform::setPosition(glm::vec3& position)
	{
		this->mPosition = position;
	}
}