#include <Brambles/Brambles.h>
#include <iostream>


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace Brambles;




int main(int argc, char* argv[])
{
	std::shared_ptr<Core> core = Core::initialize();
	

	std::shared_ptr<Entity> map = core->addEntity();
	std::shared_ptr<Renderer> mapRenderer = map->addComponent<Renderer>();

	mapRenderer->setModel(core->getResources()->load<Model>("../assets/map/c1a0.obj"));

	map->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 0.0)); 
	map->getComponent<Transform>()->setScale(glm::vec3(1.0, 1.0, 1.0)); 


	std::shared_ptr<BoxCollider> mapBoxCollider = map->addComponent<BoxCollider>();
	mapBoxCollider->setOffset(glm::vec3(0.0, 0.0, 0.0));
	mapBoxCollider->setDebugRenderer(true);
	mapBoxCollider->setSize(glm::vec3(20.0, 2.0, 20.0));
	mapBoxCollider->setOffset(glm::vec3(0.0, -13.0, -20.0));

	std::shared_ptr<RigidBody> mapRigidBody = map->addComponent<RigidBody>();
	mapRigidBody->setMass(1000000.0);
	mapRigidBody->setIsStatic(true);


	std::shared_ptr<Entity> player = core->addEntity();

	std::shared_ptr<Renderer> playerRenderer = player->addComponent<Renderer>();

	player->addComponent<PlayerController>();

	playerRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));

	player->getComponent<Transform>()->setPosition(glm::vec3(0, 0, -15.0));
	player->getComponent<Transform>()->setScale(glm::vec3(2.0, 2.0, 2.0));



	std::shared_ptr<BoxCollider> playerBoxCollider = player->addComponent<BoxCollider>();
	playerBoxCollider->setSize(glm::vec3(2.5, 4.0, 2.5));
	playerBoxCollider->setOffset(glm::vec3(0.0, 1.75, 0.0));
	playerBoxCollider->setDebugRenderer(true);

	std::shared_ptr<RigidBody> playerRigidBody = player->addComponent<RigidBody>();
	playerRigidBody->setMass(1.0);




	std::shared_ptr<Entity> camera = core->addEntity();
	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();
	camera->getComponent<Camera>()->setFov(90.0);


	

	core->run();


	return 0;
}

