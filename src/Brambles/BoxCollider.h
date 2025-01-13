#include "Component.h"

namespace Brambles
{
	struct BoxCollider : Component
	{
		bool colliding(const BoxCollider& _other);

		glm::vec3 getSize() const
		{
			return m_size;
		}

		glm::vec3 setSize(glm::vec3 _size)
		{
			m_size = _size;
		}

	private:
		glm::vec3 m_size;
		glm::vec3 m_offset;

		friend struct Entity;
		std::weak_ptr<Entity> m_entity;
		std::weak_ptr<BoxCollider> m_collider;

	};

};
