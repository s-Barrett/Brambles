#include <Brambles/Brambles.h>
#include <rend.h>
#include <iostream>



using namespace Brambles;


struct Player : Component
{
	void on_initialize()
	{
		std::cout << "init" << std::endl;
	}
	void on_tick()
	{
		std::cout << "on tick" << std::endl;
	}
	void tick()
	{
		std::cout << "tick" << std::endl;
	}	
};


int main(int argc, char *argv[])
{


	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> ent = core->add_Entity();

	std::shared_ptr<Player> p = ent->add_component<Player>();


	core->start();
	core->add_Entity();
	

	bool quit = false;	
	while (!quit)
	{
		SDL_Event event = {};

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			

		}
		
		
	}

	return 0;
}

