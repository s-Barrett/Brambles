#include <Brambles/Brambles.h>
#include <iostream>


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace Brambles;


//
//bool m_running = false;
//
//static void loop(void* _userData)
//{
//	Core* self = (Core*)_userData;
//
//	std::shared_ptr<Core> core = Core::initialize();
//	std::shared_ptr<Entity> ent = core->addEntity();
//	std::shared_ptr<Player> p = ent->addComponent<Player>();
//	std::shared_ptr<TriangleRenderer> tr = ent->addComponent<TriangleRenderer>();
//
//	tr->setTexture(core->getResources()->load<Texture>("../assets/texture.png"));
//
//	core->run();
//	core->addEntity();
//}

//void Core::run()
//{
//	m_running = true;
//#ifdef __EMSCRIPTEN__
//	emscripten_set_main_loop_arg(loop, (void*)this, 70, 1);
//#else
//	while (m_running)
//	{
//		loop((void*)this);
//	}
//#endif
//}




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
	std::shared_ptr<Renderer> render = ent->addComponent<Renderer>();
	
	ent->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));


	render->setTexture(core->getResources()->load<Texture>("../assets/walter/skycull.png"));
	render->setModel(core->getResources()->load<Model>("../assets/walter/walter.obj"));

	core->run();
	core->addEntity();
	
	return 0;
}

