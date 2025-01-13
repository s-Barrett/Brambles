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
        // Camera position and target
        glm::vec3 position = getTransform()->getPosition();
        glm::vec3 forward = getTransform()->getForward(); // Forward direction
        glm::vec3 up = getTransform()->getUp();           // Up direction

        // Target the camera is looking at
        glm::vec3 target = position + forward;

        // Use glm::lookAt to create the view matrix
        return glm::lookAt(position, target, up);
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        float aspectRatio = 4.0f / 4.0f; // Adjust aspect ratio based on your window size
        return glm::perspective(glm::radians(m_fov), aspectRatio, m_nearClip, m_farClip);
    }

    void Camera::setFov(float fov)
    {
        m_fov = fov;
    }

    void Camera::setNearClip(float nearClip)
    {
        m_nearClip = nearClip;
    }

    void Camera::setFarClip(float farClip)
    {
        m_farClip = farClip;
    }
}
