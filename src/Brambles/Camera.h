#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Component.h"

namespace Brambles
{
	struct Camera : public Component
	{
	public:
		Camera();
		~Camera();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		void setFov(float fov);
		void setNearClip(float nearClip);
		void setFarClip(float farClip);


	private:
		std::shared_ptr<Camera> m_camera;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		float m_fov = 60;
		float m_nearClip = 0.1f;
		float m_farClip = 200.0f;
	};
};
