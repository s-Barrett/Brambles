#include "Component.h"


namespace Brambles
{
	struct BoxCollider : Component
	{
	public:

		void renderDebug();

		void onRender();

		bool isColliding(std::shared_ptr<BoxCollider> _other);

		glm::vec3 getSize() { return m_size; }

		void setSize(glm::vec3 _size) { m_size = _size; }

		glm::vec3 getOffset() { return m_offset; }

		void setOffset(const glm::vec3& _offset) { m_offset = _offset; }

		void setDebugRenderer(bool _debugRenderer) { debugRenderer = _debugRenderer; }

		bool getDebugRenderer() { return debugRenderer; }

	private:
		glm::vec3 m_size{ 1 , 1 , 1 };
		glm::vec3 m_offset{ 0, 0, 0 };

		float m_mass{ 1.0f };

		bool debugRenderer = false;
	};

};
