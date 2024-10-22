#include <iostream>
#include<memory>
#include<vector>


namespace Brambles
{
	struct Entity;
	struct Window;
	struct Core
	{
		static std::shared_ptr<Core> initialize();

		void start();
		void stop();


		std::shared_ptr<Entity> add_Entity();

	private:
		std::vector<std::shared_ptr<Entity> > m_entities;
		bool m_running;
		std::weak_ptr<Core> m_self;
		std::shared_ptr<Window> m_window;
	};
}

