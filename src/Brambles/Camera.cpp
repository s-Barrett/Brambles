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

    glm::vec3 Camera::getForward() const
    {
        glm::vec3 rot = m_rotation; // rotation in degrees
        glm::vec3 forward;
        forward.x = cos(glm::radians(rot.y)) * cos(glm::radians(rot.x));
        forward.y = sin(glm::radians(rot.x));
        forward.z = sin(glm::radians(rot.y)) * cos(glm::radians(rot.x));
        return glm::normalize(forward);
    }

    glm::vec3 Camera::getUp() const
    {
        // In most cases world up is just (0, 1, 0)
        return glm::vec3(0.0f, 1.0f, 0.0f);
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

        // Calculate the right vector (considering roll)
        glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));

        // Recalculate up vector to include roll
        glm::vec3 up = glm::normalize(glm::cross(right, forward));

        // Apply roll rotation to the up vector
        if (m_rotation.z != 0.0f) {
            float rollRad = glm::radians(m_rotation.z);
            glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), rollRad, forward);
            up = glm::vec3(rollMatrix * glm::vec4(up, 0.0f));
        }

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
