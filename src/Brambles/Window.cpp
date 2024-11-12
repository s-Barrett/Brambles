#include "Window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Brambles
{
	Window::Window()
	{

		int WINDOW_WIDTH = 700;
		int WINDOW_HEIGHT = 700;

		m_raw = SDL_CreateWindow("Brambles Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);


		if (!m_raw)
		{
			std::cerr << "Window creation failed" << std::endl;
			return;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		m_context = SDL_GL_CreateContext(m_raw);
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_raw);
		SDL_Quit();
	}


	rend::ivec2 Window::size()
	{
		rend::ivec2 rtn;
		SDL_GetWindowSize(m_raw, &rtn.x, &rtn.y);
		return rtn;
	}	


}