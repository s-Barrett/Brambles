#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Brambles
{

	glm::mat4 Transform::getModelMatrix() const
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, m_scale);

		return modelMatrix;
	}

	glm::vec3 Transform::getForward() const
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
		forward.y = sin(glm::radians(m_rotation.x));
		forward.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));

		return glm::normalize(forward);
	}

	glm::vec3 Transform::getRight() const
	{
		glm::vec3 right;
		right.x = sin(glm::radians(m_rotation.y) - 3.14f / 2.0f);
		right.y = 0;
		right.z = cos(glm::radians(m_rotation.y) - 3.14f / 2.0f);

		return glm::normalize(right);
	}

	glm::vec3 Transform::getUp() const
	{
		glm::vec3 up;
		glm::vec3 forward = getForward();
		glm::vec3 right = getRight();

		up = glm::cross(right, forward);

		return glm::normalize(up);
	}
}