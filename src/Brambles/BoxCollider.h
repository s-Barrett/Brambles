#include "Component.h"


namespace Brambles
{
	struct BoxCollider : Component
	{
	public:
		bool isColliding(std::shared_ptr<BoxCollider> _other);

		glm::vec3 getSize() { return m_size; }

		glm::vec3 setSize(glm::vec3 _size) { m_size = _size; }

		glm::vec3 getOffset() { return m_offset; }

		glm::vec3 setOffset(glm::vec3 _offset) { m_offset = _offset; }

	private:
		glm::vec3 m_size{ 1 };
		glm::vec3 m_offset{ 0 };

	};

};
