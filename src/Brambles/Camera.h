
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

		glm::vec3 getCameraPosition();

		void setCameraPosition(glm::vec3 pos);

		void setCameraRotation(glm::vec3 rot);

		glm::vec3 getCameraRotation();

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

        void setPriority(float _priority) { m_priority = _priority; }

        float getPriority() { return m_priority; }

    private:
        std::shared_ptr<Camera> m_camera; ///< The camera instance.

        glm::vec3 m_position = glm::vec3(0, 0, 0); ///< Camera's position in 3D space.
        glm::vec3 m_rotation = glm::vec3(0, 0, 0); ; ///< Camera's rotation in 3D space.
        glm::mat4 m_projection; ///< The camera's projection matrix.
        glm::mat4 m_view; ///< The camera's view matrix.
        float m_fov = 60; ///< The camera's field of view.
        float m_nearClip = 0.1f; ///< The near clipping plane distance.
        float m_farClip = 200.0f; ///< The far clipping plane distance.
		float m_priority = 1.0f; ///< The camera's priority for rendering.


    };
};
