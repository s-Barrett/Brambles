#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "Camera.h"
#include "Input.h"
#include "Resources/Audio.h"
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
		rtn->m_audio = std::make_shared<Audio>();
		rtn->m_camera = std::make_shared<Camera>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_input = std::make_shared<Input>();
		rtn->m_self = rtn;
		

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_self = rtn; // Initialize m_self first
		rtn->m_core = m_self; // Assign the Core reference

		// Debug logging
		std::cout << "Entity created with m_self and m_core initialized." << std::endl;

		// Assertions to ensure m_self and m_core are set
		assert(!rtn->m_self.expired() && "m_self is not properly initialized.");
		assert(!rtn->m_core.expired() && "m_core is not properly initialized.");

		rtn->addComponent<Transform>(); // Now add components safely

		m_entities.push_back(rtn);
		return rtn;
	}

	template <typename T>
	std::shared_ptr<T> Core::seekComponent()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			std::shared_ptr<Entity> e = m_entities.at(ei);

			for (size_t ci = 0; ci < e->m_components.size(); ++ci)
			{
				std::shared_ptr<Component> c = e->m_components.at(ci);
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);

				if (t)
				{
					return t;
				}
			}
		}

		return nullptr;
	}

	template <typename T>
	void Core::seekComponents(std::vector<std::shared_ptr<T>>& _out)
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			std::shared_ptr<Entity> e = m_entities.at(ei);
			for (size_t ci = 0; ci < e->m_components.size(); ++ci)
			{
				std::shared_ptr<Component> c = e->m_components.at(ci);
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);

				if (t)
				{
					_out.push_back(t);
				}
			}
		}
	}

	std::shared_ptr<Camera> Core::getCamera()
	{
		std::vector<std::shared_ptr<Camera>> cameras;
		seekComponents(cameras);

		if (cameras.size() == 0)
		{
			std::cout << "No entity with a camera component found" << std::endl;
			throw std::exception();
			return nullptr;
		}

		std::shared_ptr<Camera> rtn = cameras[0];
	
		rtn = cameras[0];

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
				if (e.type == SDL_MOUSEMOTION)
				{
					m_input->mouseX += e.motion.xrel;
					m_input->mouseY += e.motion.yrel;
				}
				else
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
				else if(e.type == SDL_KEYDOWN)
				{
					m_input->keys.push_back(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					for (size_t i = 0; i < m_input->keys.size(); i++)
					{
						if (m_input->keys[i] == e.key.keysym.sym)
						{
							m_input->keys.erase(m_input->keys.begin() + i);
							--i;
						}
					}
				}
			}
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->onTick();
			}


			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->onRender();
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
