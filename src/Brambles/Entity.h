#pragma once
#include <iostream>
#include <memory>
#include <vector>


namespace Brambles
{
	struct Core;
	struct Component;

	struct Entity
	{
	public:
		std::shared_ptr<Core> getCore();
	
		template <typename T, typename... Args>
		std::shared_ptr<T> addComponent(Args&&... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
			component->m_entity = m_self; // Set the m_entity weak pointer
			m_components.push_back(component);
			component->onInitialize();
			return component;
		}

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


	private:
		friend struct Brambles::Core;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;

		std::vector<std::shared_ptr<Component>> m_components;



		void onTick();
		void onRender();

	};

}