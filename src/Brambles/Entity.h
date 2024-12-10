#include <iostream>
#include <memory>
#include <vector>


namespace Brambles
{
	struct Core;
	struct Component;
	struct Transform;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->onInitialize();
			m_components.push_back(rtn);

			/*addComponent<T>() : std::shared_ptr<T>;

			addComponent<T, A>(a:A) : std::shared_ptr<T>;

			addComponent<T, A, B>(a:A, b : B) : std::shared_ptr<T>;

			addComponent<T, A, B, C>(a:A, b : B, c : C) : std::shared_ptr<T>;*/


			return rtn;
		}

		std::shared_ptr<Transform> getTransform() { return m_transform; }
		



	private:
		friend struct Brambles::Core;
		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;
		std::shared_ptr<Transform> m_transform;
		std::vector<std::shared_ptr<Component> > m_components;

		void tick();
		void render();
	};

}