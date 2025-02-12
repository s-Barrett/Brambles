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
	std::shared_ptr<Core> core = Core::initialize();
	

	std::shared_ptr<Entity> map = core->addEntity();
	std::shared_ptr<Renderer> mapRenderer = map->addComponent<Renderer>();

	mapRenderer->setTexture(core->getResources()->load<Texture>("../assets/map/map2.png"));
	mapRenderer->setModel(core->getResources()->load<Model>("../assets/map/map.obj"));

	map->getComponent<Transform>()->setPosition(glm::vec3(0, 15, 20.0)); 
	map->getComponent<Transform>()->setScale(glm::vec3(10, 10, 10)); 


	std::shared_ptr<BoxCollider> mapBoxCollider = map->addComponent<BoxCollider>();
	mapBoxCollider->setOffset(glm::vec3(0.0, 0.0, 0.0));
	mapBoxCollider->setDebugRenderer(true);
	mapBoxCollider->setSize(glm::vec3(20.0, 2.0, 20.0));
	mapBoxCollider->setOffset(glm::vec3(0.0, -23.0, -40.0));

	std::shared_ptr<RigidBody> mapRigidBody = map->addComponent<RigidBody>();
	mapRigidBody->setMass(1000000000.0);
	mapRigidBody->setIsStatic(true);


	


	std::shared_ptr<Entity> player = core->addEntity();
	std::shared_ptr<Renderer> playerRenderer = player->addComponent<Renderer>();

	playerRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));	
	playerRenderer->setTexture(core->getResources()->load<Texture>("../assets/objects/walter/skycull.png"));

	player->getComponent<Transform>()->setPosition(glm::vec3(0, -8, -20));
	player->getComponent<Transform>()->setScale(glm::vec3(5.0, 5.0, 5.0));
	player->addComponent<PlayerController>();

	std::shared_ptr<BoxCollider> playerBoxCollider = player->addComponent<BoxCollider>();
	playerBoxCollider->setDebugRenderer(true);
	playerBoxCollider->setSize(glm::vec3(4.0, 7.0, 4.0));
	playerBoxCollider->setOffset(glm::vec3(0.0, 5.0, 0.0));
	std::shared_ptr<RigidBody> playerRigidBody = player->addComponent<RigidBody>();
	playerRigidBody->setMass(10.0);


	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<Renderer> entityRenderer = entity->addComponent<Renderer>();

	entityRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));
	entityRenderer->setTexture(core->getResources()->load<Texture>("../assets/objects/walter/skycull.png"));

	entity->getComponent<Transform>()->setPosition(glm::vec3(-10, -8, -20));
	entity->getComponent<Transform>()->setScale(glm::vec3(5.0, 5.0, 5.0));


	std::shared_ptr<BoxCollider> entityBoxCollider = entity->addComponent<BoxCollider>();
	entityBoxCollider->setDebugRenderer(true);
	entityBoxCollider->setSize(glm::vec3(4.0, 7.0, 4.0));
	entityBoxCollider->setOffset(glm::vec3(0.0, 5.0, 0.0));
	std::shared_ptr<RigidBody> entityRigidBody = entity->addComponent<RigidBody>();
	entityRigidBody->setMass(100.0);
	



	std::shared_ptr<Entity> camera = core->addEntity();
	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();
	camera->getComponent<Camera>()->setFov(90.0);


	

	core->run();


	return 0;
}

