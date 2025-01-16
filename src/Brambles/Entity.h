#pragma once
#include <iostream>
#include <memory>
#include <vector>

namespace Brambles
{
    struct Core;
    struct Component;


	/**
	 * @brief Defines the base class for entities in the engine.
	 */
    struct Entity
    {
    public:
        /**
         * @brief Gets the core the entity belongs to.
         * @return A shared pointer to the core.
         */
        std::shared_ptr<Core> getCore();

        /**
         * @brief Adds a new component to the entity.
         * @param args Arguments to pass to the component's constructor.
         * @return A shared pointer to the added component.
         */
        template <typename T, typename... Args>
        std::shared_ptr<T> addComponent(Args&&... args)
        {
            std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
            component->m_entity = m_self; // Set the m_entity weak pointer
            m_components.push_back(component);
            component->onInitialize();
            return component;
        }

        /**
         * @brief Gets a component of the specified type from the entity.
         * @tparam T The type of component to get.
         * @return A shared pointer to the component, or nullptr if not found.
         */
        template <typename T>
        std::shared_ptr<T> getComponent()
        {
            for (size_t i = 0; i < m_components.size(); ++i)
            {
                std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_components[i]);
                if (rtn)
                {
                    return rtn;
                }
            }

            return nullptr;
        }

        /**
         * @brief Checks if the entity has a component of the specified type.
         * @tparam T The type of component to check.
         * @return A shared pointer to the component if found, or nullptr if not.
         */
        template <typename T>
        std::shared_ptr<T> hasComponent()
        {
            for (size_t i = 0; i < m_components.size(); ++i)
            {
                std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_components[i]);
                if (rtn)
                {
                    return rtn;
                }
            }

            return nullptr;
        }

    private:
        friend struct Brambles::Core;

        std::weak_ptr<Core> m_core; ///< Weak pointer to the core.
        std::weak_ptr<Entity> m_self; ///< Weak pointer to the entity itself.

        std::vector<std::shared_ptr<Component>> m_components; ///< List of components attached to the entity.

        void onTick();
        void onRender();
        void onGui();
    };

}
