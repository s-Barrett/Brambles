#include "Entity.h"
#include "Component.h"
#include "Core.h"

namespace Brambles
{
    // Get the core associated with the entity
    std::shared_ptr<Core> Entity::getCore()
    {
        return m_core.lock();
    }

    // Call tick on all components
    void Entity::onTick()
    {
        for (size_t ci = 0; ci < m_components.size(); ++ci)
        {
            m_components.at(ci)->tick();
        }
    }

    // Call render on all components
    void Entity::onRender()
    {
        for (size_t ci = 0; ci < m_components.size(); ++ci)
        {
            m_components.at(ci)->render();
        }
    }

    // Call gui on all components
    void Entity::onGui()
    {
        for (size_t ci = 0; ci < m_components.size(); ++ci)
        {
            m_components.at(ci)->gui();
        }
    }
}
