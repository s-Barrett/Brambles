#include <Brambles/Brambles.h>
#include <iostream>



using namespace Brambles;


struct Player : Component
{
	void on_initialize()
	{
		std::cout << "player init" << std::endl;
	}
	void on_tick()
	{
		std::cout << "player tick" << std::endl;
	}
	void tick()
	{
		std::cout << "player tick" << std::endl;
	}	
};


int main(int argc, char *argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> ent = core->add_Entity();

	std::shared_ptr<Player> p = ent->add_component<Player>();




	//core->add_Entity();
	core->start();

	return 0;
}