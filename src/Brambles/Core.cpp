#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "rend/rend.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>


namespace Brambles
{

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_window = std::make_shared<Window>();
		rtn->m_self = rtn;
		

		return rtn;
	}

	std::shared_ptr<Entity> Core::add_Entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_core = m_self;
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


			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{

			}


			rend::Texture tex("../assets/texture.png");

			rend::Mesh quad;
			rend::Face tri;

			tri.a.position = rend::vec3(0, 0, 0);
			tri.b.position = rend::vec3(1, 0, 0);
			tri.c.position = rend::vec3(0, 1, 0);

			quad.addFace(tri);


			glBindVertexArray(quad.getVAOId());
			glDrawArrays(GL_TRIANGLES, 0, quad.vertexCount());

		}
		stop();
	}


	void Core::stop()
	{
		return;
	}

}
