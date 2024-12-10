#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Brambles
{

	glm::mat4 Transform::getModelMatrix() const
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_Position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, m_Scale);

		return modelMatrix;
	}

	glm::vec3 Transform::getPosition()
	{
		return m_Position;
	}

	void Transform::setPosition(glm::vec3& position)
	{
		this->m_Position = position;
	}
}