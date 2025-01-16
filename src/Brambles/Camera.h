
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Component.h"

namespace Brambles
{
    struct Core;

	/**
	 * @brief Defines the Camera component for handling view and projection matrices.
	 */
    struct Camera : public Component
    {
    public:
        Camera();
        ~Camera();

        /**
         * @brief Gets the view matrix of the camera.
         * @return The view matrix.
         */
        glm::mat4 getViewMatrix();

        /**
         * @brief Gets the projection matrix of the camera.
         * @return The projection matrix.
         */
        glm::mat4 getProjectionMatrix();

        /**
         * @brief Sets the field of view (FOV) for the camera.
         * @param fov The field of view to set.
         */
        void setFov(float fov);

        /**
         * @brief Sets the near clipping plane distance for the camera.
         * @param nearClip The near clipping plane distance to set.
         */
        void setNearClip(float nearClip);

        /**
         * @brief Sets the far clipping plane distance for the camera.
         * @param farClip The far clipping plane distance to set.
         */
        void setFarClip(float farClip);

    private:
        std::shared_ptr<Camera> m_camera; ///< The camera instance.

        glm::vec3 m_position; ///< Camera's position in 3D space.
        glm::vec3 m_rotation; ///< Camera's rotation in 3D space.
        glm::mat4 m_projection; ///< The camera's projection matrix.
        glm::mat4 m_view; ///< The camera's view matrix.
        float m_fov = 60; ///< The camera's field of view.
        float m_nearClip = 0.1f; ///< The near clipping plane distance.
        float m_farClip = 200.0f; ///< The far clipping plane distance.
    };
};
