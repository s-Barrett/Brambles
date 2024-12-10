#include "Entity.h"
#include "Component.h"


namespace Brambles
{
	std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}
	void Entity::tick()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->tick();
		}
	}
	void Entity::render()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->render();

		}
	}

}