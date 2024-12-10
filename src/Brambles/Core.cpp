#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "rend/rend.h"
#include "Resources.h"
#include <stb_image.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Transform.h"


namespace Brambles
{

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_window = std::make_shared<Window>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_self = rtn;
		

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_self = rtn;
		rtn->m_core = m_self;
	
		rtn->addComponent<Transform>();

		m_entities.push_back(rtn);

		return rtn;

	}

	void Core::run()
	{
		bool running = true;
		SDL_Event e;
		while (running)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
			}
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->tick();
			}


			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (size_t i = 0; i < m_entities.size(); ++i)
			{				
					m_entities[i]->render();				
			}	

			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->tick();
			}
	
			SDL_GL_SwapWindow(m_window->m_raw);
		}
		stop();
	}


	void Core::stop()
	{
		return;
	}

}
