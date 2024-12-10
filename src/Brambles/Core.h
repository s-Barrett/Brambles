#include <iostream>
#include<memory>
#include<vector>


namespace Brambles
{
	struct Entity;
	struct Window;
	struct Screen;
	struct Gui;
	struct Resources;
	struct Core
	{

		static std::shared_ptr<Core> initialize();
		
		void run();
		void stop();

		std::shared_ptr<Entity> addEntity();

		std::shared_ptr<Window> getWindow() { return m_window; }

		std::shared_ptr<Resources> getResources() { return m_resources; }



	private:

		std::shared_ptr<Window> m_window;
		std::shared_ptr<Resources> m_resources;
		std::shared_ptr<Gui> m_gui;

		std::vector<std::shared_ptr<Entity> > m_entities;

		std::weak_ptr<Core> m_self;
		
	};
}

