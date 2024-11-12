#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "rend/rend.h"
#include <stb_image.h>
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

	std::shared_ptr<Entity> Core::addEntity()
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

			float angleY = 0;
			float angleX = 0;
			float angleZ = 0;

			glm::vec3 campos(0, 0, 0);
			glm::vec3 camrot(0, 0, 0);
			float sensitivity = 0.1f; // Adjust the sensitivity as needed
			
			rend::Shader normalShader("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl");
			
			rend::Texture tex("../assets/texture.png");

			rend::Mesh triangle;
			rend::Face a;

			a.a.position = glm::vec3(-1, -1, 0);
			a.b.position = glm::vec3(1, -1, 0);
			a.c.position = glm::vec3(0, 1, 0);

			triangle.addFace(a);
			

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0, -10, -30.5f));
			model = glm::rotate(model, glm::radians(angleY), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(angleX), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0, 0, 1));




			//prepare view matrix
			glm::mat4 view(1.0f);
			view = glm::translate(view, campos);
			view = glm::rotate(view, glm::radians(camrot.y), glm::vec3(0, 1, 0));
			view = glm::rotate(view, glm::radians(camrot.x), glm::vec3(1, 0, 0));
			view = glm::inverse(view);

			normalShader.use();


			normalShader.uniform("u_View", view);
			normalShader.uniform("u_Model", model);

			glBindVertexArray(triangle.getVAOId());
			glUseProgram(normalShader.id());
			glBindTexture(GL_TEXTURE_2D, tex.id());

			glDrawArrays(GL_TRIANGLES, 0, triangle.vertexCount());

		}
		stop();
	}


	void Core::stop()
	{
		return;
	}

}
