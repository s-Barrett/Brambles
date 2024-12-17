#include "Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	class Transform : public Component
	{
	public:
		void setPosition(glm::vec3 _position) { m_Position = _position; }
		glm::vec3 GetPosition() { return m_Position; }

		void setRotation(glm::vec3 _rotation) { m_Rotation = _rotation; }
		glm::vec3 GetRotation() { return m_Rotation; }

		void setScale(glm::vec3 _scale) { m_Scale = _scale; }
		glm::vec3 GetScale() { return m_Scale; }

		void move(glm::vec3 _movement) { m_Position += _movement; }
		void rotate(glm::vec3 _rotation) { m_Rotation += _rotation; }
		void scale(glm::vec3 _scale) { m_Scale += _scale; }

		glm::mat4 getModelMatrix() const;
		glm::vec3 Transform::getPosition();
		void Transform::setPosition(glm::vec3& position);

	private:
		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::vec3 m_Scale{ 1.0f };
	};
}