#include "Camera.h"
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
        glm::mat4 view(1.0f);
        view = glm::translate(view, -getPosition());
        view = glm::rotate(view, glm::radians(getRotation().x), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(getRotation().y), glm::vec3(0, 1, 0));
        view = glm::rotate(view, glm::radians(getRotation().z), glm::vec3(0, 0, 1));
        return view;
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        float aspectRatio = 4.0f / 4.0f; 
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
