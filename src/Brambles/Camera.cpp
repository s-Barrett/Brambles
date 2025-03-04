#include "Camera.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Brambles
{
    Camera::Camera()
    {
    }

    Camera::~Camera()
    {
    }

	glm::vec3 Camera::getCameraPosition()
	{
		return getTransform()->getPosition();
	}

    void Camera::setCameraPosition(glm::vec3 pos)
    {
		m_position = pos;
    }

    glm::vec3 Camera::getCameraRotation()
    {
		return m_rotation;
    }

    void Camera::setCameraRotation(glm::vec3 rot)
    {
		m_rotation = rot;
    }

    glm::mat4 Camera::getViewMatrix()
    {
        // Get the camera's position
        glm::vec3 position = getTransform()->getPosition() + m_position;

        // Calculate the forward direction based on the camera's rotation (pitch and yaw)
        glm::vec3 forward;
        forward.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
        forward.y = sin(glm::radians(m_rotation.x));
        forward.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
        forward = glm::normalize(forward);

        // Calculate the right and up vectors
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));

        // Calculate the target position the camera is looking at
        glm::vec3 target = position + forward;

        // Generate view matrix using glm::lookAt
        return glm::lookAt(position, target, up);
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        float aspectRatio = 4.0f / 4.0f; // Placeholder aspect ratio, should be updated dynamically
        return glm::perspective(glm::radians(m_fov), aspectRatio, m_nearClip, m_farClip);
    }

    void Camera::setFov(float fov)
    {
        m_fov = fov; // Set field of view
    }

    void Camera::setNearClip(float nearClip)
    {
        m_nearClip = nearClip; // Set near clipping plane
    }

    void Camera::setFarClip(float farClip)
    {
        m_farClip = farClip; // Set far clipping plane
    }
}
