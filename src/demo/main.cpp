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



int main(int argc, char* argv[])
{
	CameraController;



	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> map = core->addEntity();
	map->addComponent<Transform>();
	std::shared_ptr<Renderer> mapp = map->addComponent<Renderer>();

	mapp->setTexture(core->getResources()->load<Texture>("../assets/map/map2.png"));
	mapp->setModel(core->getResources()->load<Model>("../assets/map/map.obj"));

	map->getComponent<Transform>()->setPosition(glm::vec3(0, 15, 0.0));
	map->getComponent<Transform>()->setScale(glm::vec3(10, 10, 10));

	std::shared_ptr<BoxCollider> mapbc = map->addComponent<BoxCollider>();
	

	std::shared_ptr<Entity> camera = core->addEntity();
	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();
	camera->getComponent<Camera>()->setFov(90.0);


	std::shared_ptr<Entity> entity = core->addEntity();
	entity->addComponent<PlayerController>();
	entity->addComponent<Transform>();
	entity->getComponent<Transform>()->setScale(glm::vec3(5, 5, 5));
	entity->getComponent<Transform>()->setPosition(glm::vec3(2, -9, -25.0));
	entity->addComponent<RigidBody>();
	std::shared_ptr<BoxCollider> ebc = entity->addComponent<BoxCollider>();
	//entity->getComponent<BoxCollider>()->setSize(glm::vec3(1.0, 2.0, 1.0));
	//entity->getComponent<RigidBody>()->setDebugRenderer(false);
	std::shared_ptr<Renderer> entityRender = entity->addComponent<Renderer>();

	entityRender->setTexture(core->getResources()->load<Texture>("../assets/objects/walter/skycull.png"));
	entityRender->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));

	std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();

	std::shared_ptr<Entity> entity2 = core->addEntity();
	entity2->addComponent<Transform>();
	entity2->getComponent<Transform>()->setScale(glm::vec3(1.0, 1.0, 1.0));
	entity2->getComponent<Transform>()->setPosition(glm::vec3(10, -9, -20.0));
	std::shared_ptr<BoxCollider> ebc2 = entity2->addComponent<BoxCollider>();
	//entity2->addComponent<RigidBody>();
	//entity2->getComponent<RigidBody>()->setDebugRenderer(true);
	//entity2->getComponent<BoxCollider>()->setOffset(glm::vec3(0.0, 2.0, 0.0));
	entity2->getComponent<BoxCollider>()->setSize(glm::vec3(1.0, 2.0, 1.0));
	std::shared_ptr<Renderer> entityRender2 = entity2->addComponent<Renderer>();

	entityRender2->setTexture(core->getResources()->load<Texture>("../assets/objects/headcrab/headcrab.png"));
	entityRender2->setModel(core->getResources()->load<Model>("../assets/objects/headcrab/headcrab.obj"));


	sound->setSound(core->getResources()->load<Sound>("../assets/sounds/halflife/hellofreeman"));
	sound->play();

	

	core->run();


	return 0;
}

