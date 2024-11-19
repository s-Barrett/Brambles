#include <Brambles/Brambles.h>
#include <iostream>



using namespace Brambles;



struct Player : Component
{
	void onInitialize()
	{
		std::cout << "init" << std::endl;
	}
	void onTick()
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

	std::shared_ptr<Entity> ent = core->addEntity();

	std::shared_ptr<Player> p = ent->addComponent<Player>();

	std::shared_ptr<TriangleRenderer> tr = ent->addComponent<TriangleRenderer>();

	core->getResources()->load<Texture>("res/texture.png");


	core->run();
	core->addEntity();
	

	return 0;
}

