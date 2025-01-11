#include "Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	struct Transform : public Component
	{
	public:
	

		void setPosition(glm::vec3 _position) { m_position = _position; }

		glm::vec3 getPosition() { return m_position; }

		void setRotation(glm::vec3 _rotation) { m_rotation = _rotation; }

		glm::vec3 getRotation() { return m_rotation; }

		void setScale(glm::vec3 _scale) { m_scale = _scale; }

		glm::vec3 getScale() { return m_scale; }


		void move(glm::vec3 _movement) { m_position += _movement; }
		void rotate(glm::vec3 _rotation) { m_rotation += _rotation; }
		void scale(glm::vec3 _scale) { m_scale += _scale; }

		glm::vec3 getForward() const;
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;

		glm::mat4 getModelMatrix() const;


	private:
		glm::vec3 m_position{ 0.0f };
		glm::vec3 m_rotation{ 0.0f };
		glm::vec3 m_scale{ 1.0f };
	};
}