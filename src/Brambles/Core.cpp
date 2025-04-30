#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "Camera.h"
#include "Input.h"
#include "Gui.h"
#include "Timer.h"
#include "LightManager.h"
#include "Resources/Audio.h"
#include "Physics.h"
#include "rend/rend.h"
#include "Resources.h"
#include <stb_image.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Transform.h"

namespace Brambles
{
	// Initializes the core systems and returns a shared pointer to Core
	std::shared_ptr<Core> Core::initialize(int winsizeX, int winsizeY)
	{
		// Create the window with the given size
	
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_window = std::make_shared<Window>(winsizeX, winsizeY);
		rtn->m_lightManager = std::make_shared<LightManager>();
		rtn->m_audio = std::make_shared<Audio>();
		rtn->m_camera = std::make_shared<Camera>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_physics = std::make_shared<Physics>();
		rtn->m_timer = std::make_shared<Timer>();
		rtn->m_input = std::make_shared<Input>();
		rtn->m_gui = std::make_shared<Gui>();
		rtn->m_self = rtn;

		return rtn;
	}

	// Adds a new entity to the core and initializes required components
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_self = rtn;
		rtn->m_core = m_self;

		std::cout << "Entity created with m_self and m_core initialized." << std::endl;

		// Ensure that the entity has been properly initialized
		assert(!rtn->m_self.expired() && "m_self is not properly initialized.");
		assert(!rtn->m_core.expired() && "m_core is not properly initialized.");

		// Attach necessary components
		rtn->addComponent<Transform>();
		rtn->addComponent<Timer>();
		rtn->getComponent<Timer>()->start();

		m_entities.push_back(rtn);
		return rtn;
	}


	// Retrieves the first Timer component in the scene
	std::shared_ptr<Timer> Core::getTimer()
	{
		std::vector<std::shared_ptr<Timer>> timers;
		seekComponents(timers);

		if (timers.empty())
		{
			std::cout << "No entity with a timer component found" << std::endl;
			throw std::exception();
		}

		return timers[0];
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
		for (size_t i = 1; i < cameras.size(); ++i)
		{
			if (cameras[i]->getPriority() > rtn->getPriority())
			{
				rtn = cameras[i];
			}
		}

		return rtn;
	}


	// Main game loop
	void Core::run()
	{
		bool running = true;
		SDL_Event e;

		while (running)
		{
			// Handle input events
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_MOUSEMOTION)
				{
					m_input->mouseX += e.motion.xrel;
					m_input->mouseY += e.motion.yrel;
				}
				else if (e.type == SDL_QUIT)
				{
					running = false;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					m_input->keys.push_back(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					// Remove released key from active keys list
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

			getTimer()->update();

			getPhysics()->update(getTimer()->getDeltaTime());

			// Update all entities
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->onTick();
			}

			// Clear the screen

			
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render entities
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->onRender();
			}

			glEnable(GL_DEPTH_TEST);

			// Render GUI elements
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				m_entities[ei]->onGui();
			}

			glEnable(GL_DEPTH_TEST);



			// Swap buffers to display the rendered frame
			SDL_GL_SwapWindow(m_window->m_raw);
		}

		stop();
	}

	void Core::runSingleFrame()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				m_input->mouseX += e.motion.xrel;
				m_input->mouseY += e.motion.yrel;
			}
			else if (e.type == SDL_QUIT)
			{
				stop(); // optionally set a flag here if you want to stop Emscripten's loop
				return;
			}
			else if (e.type == SDL_KEYDOWN)
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

		getTimer()->update();
		getPhysics()->update(getTimer()->getDeltaTime());

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

		glEnable(GL_DEPTH_TEST);

		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities[ei]->onGui();
		}

		glEnable(GL_DEPTH_TEST);

		SDL_GL_SwapWindow(m_window->m_raw);
	}

	// Stops the engine (currently does nothing)
	void Core::stop()
	{
		return;
	}

}
