#include <iostream>
#include <memory>
#include <vector>


namespace Brambles
{
	struct Core;
	struct Component;

	struct Entity
	{
		std::shared_ptr<Core> Entity::getCore();
	
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_entity = m_self.lock(); 
			rtn->onInitialize();
			m_components.push_back(rtn);

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> GetComponent()
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



		std::vector<std::shared_ptr<Component> > m_components;



		void tick();
		void render();

	};

}