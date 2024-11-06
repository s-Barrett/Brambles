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

		void run();
		void stop();


		std::shared_ptr<Entity> add_Entity();

		std::shared_ptr<Window> get_Window() { return m_window; }

	private:
		std::shared_ptr<Window> m_window;
		std::vector<std::shared_ptr<Entity> > m_entities;
		bool m_running = true;
		std::weak_ptr<Core> m_self;
		
	};
}

