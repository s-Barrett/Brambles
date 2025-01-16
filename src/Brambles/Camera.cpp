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

    glm::mat4 Camera::getViewMatrix()
    {
        glm::vec3 position = getTransform()->getPosition();
        glm::vec3 forward = getTransform()->getForward();
        glm::vec3 up = getTransform()->getUp();

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
