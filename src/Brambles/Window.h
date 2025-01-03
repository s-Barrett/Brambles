#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <memory.h>
#include <iostream>

namespace Brambles
{
	struct Core;
	struct Window
	{
		Window();
		~Window();

		rend::ivec2 size();

		int WINDOW_WIDTH = 700;
		int WINDOW_HEIGHT = 700;

	private:
		friend struct Brambles::Core;
		SDL_Window* m_raw;

		SDL_GLContext m_context;

		Window(const Window& _copy);
		Window& operator=(const Window& _assign);

	};

}