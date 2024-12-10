#include "Component.h"
#include <glm/glm.hpp>


namespace Brambles
{
	class Transform : public Component
	{
	public:
		void SetPosition(glm::vec3 _position) { m_Position = _position; }
		glm::vec3 GetPosition() { return m_Position; }

		void SetRotation(glm::vec3 _rotation) { m_Rotation = _rotation; }
		glm::vec3 GetRotation() { return m_Rotation; }

		void SetScale(glm::vec3 _scale) { m_Scale = _scale; }
		glm::vec3 GetScale() { return m_Scale; }

		glm::mat4 getModelMatrix() const;
		glm::vec3 Transform::getPosition();
		void Transform::setPosition(glm::vec3& position);

	private:
		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::vec3 m_Scale{ 1.0f };
	};
}