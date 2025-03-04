#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace Brambles
{
	glm::mat4 Transform::getModelMatrix() const //Get the model matrix
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        
        modelMatrix = glm::translate(modelMatrix, m_position);

        
        modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
        modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
        modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

      
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
        // Calculate right vector as the cross product of forward and world up
        glm::vec3 forward = getForward();
        glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
        return glm::normalize(right);
    }

    glm::vec3 Transform::getUp() const
    {
        glm::vec3 forward = getForward();
        glm::vec3 right = getRight();
        return glm::normalize(glm::cross(right, forward));
    }
}
