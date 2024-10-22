#include "Core.h"
#include "Entity.h"
//#include "Window.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>


namespace Brambles
{

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;
		//rtn->m_window = std::make_shared<Window>();


		return rtn;
	}

	std::shared_ptr<Entity> Core::add_Entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_core = m_self;
		m_entities.push_back(rtn);

		return rtn;

	}



	void Core::start()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities[ei]->tick();
		}
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			
		}
	}

	void Core::stop()
	{
		return;
	}

}
