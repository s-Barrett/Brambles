#include <Brambles/Brambles.h>
#include <iostream>


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace Brambles;




int main(int argc, char* argv[])
{

	int winsizeX = 1920;
	int winsizeY = 1080;


	std::shared_ptr<Core> core = Core::initialize(winsizeX, winsizeY);
	
	core->getLightManager()->setAmbient(glm::vec3(0.1, 0.1, 0.1));
	core->getLightManager()->addLight("light1", glm::vec3(8.0, 5.0, -10.0), glm::vec3(1.0, 1.0, 0.9), 0.9);
	core->getLightManager()->addLight("light2", glm::vec3(-14.0, 5.0, -10.0), glm::vec3(1.0, 1.0, 0.9), 0.9);

	core->getLightManager()->addLight("light3", glm::vec3(10.0, -180.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 0.3);

	core->getLightManager()->addLight("light4", glm::vec3(0.0, -10.0, -10.0), glm::vec3(0.1, 0.1, 1.0), 0.3);


	std::shared_ptr<Entity> map = core->addEntity();
	std::shared_ptr<Renderer> mapRenderer = map->addComponent<Renderer>();

	mapRenderer->setModel(core->getResources()->load<Model>("../assets/map/c1a0.obj"));

	map->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 0.0)); 
	map->getComponent<Transform>()->setScale(glm::vec3(1.0, 1.0, 1.0)); 


	std::shared_ptr<BoxCollider> mapBoxCollider = map->addComponent<BoxCollider>();
	mapBoxCollider->setDebugRenderer(true);
	mapBoxCollider->setSize(glm::vec3(30.0, 1.0, 30.0));
	mapBoxCollider->setOffset(glm::vec3(0.0, -12.5, -20.0));

	std::shared_ptr<RigidBody> mapRigidBody = map->addComponent<RigidBody>();
	mapRigidBody->setMass(1000000.0);
	mapRigidBody->setIsStatic(true);


	std::shared_ptr<Entity> player = core->addEntity();

	std::shared_ptr<Renderer> playerRenderer = player->addComponent<Renderer>();

	player->addComponent<PlayerController>();

	playerRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));

	player->getComponent<Transform>()->setPosition(glm::vec3(0, -10, -15.0));
	player->getComponent<Transform>()->setScale(glm::vec3(2.0, 2.0, 2.0));
	player->getComponent<Transform>()->setRotation(glm::vec3(0.0, 180.0, 0.0));

	std::shared_ptr<Camera> playerCamera = player->addComponent<Camera>();
	playerCamera->setFov(80.0);
	playerCamera->setCameraPosition(glm::vec3(0, 4.0, 0));
	playerCamera->setPriority(1.0);

	std::shared_ptr<AudioSource> audioSource = player->addComponent<AudioSource>();



	std::shared_ptr<BoxCollider> playerBoxCollider = player->addComponent<BoxCollider>();
	playerBoxCollider->setSize(glm::vec3(1.0, 3.7, 1.0));
	playerBoxCollider->setOffset(glm::vec3(0.0, 1.75, 0.0));
	playerBoxCollider->setDebugRenderer(true);

	std::shared_ptr<RigidBody> playerRigidBody = player->addComponent<RigidBody>();
	playerRigidBody->setMass(200.0);


	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<Renderer> entityRenderer = entity->addComponent<Renderer>();

	entityRenderer->setModel(core->getResources()->load<Model>("../assets/objects/medkit/Medkit.obj"));

	entity->getComponent<Transform>()->setPosition(glm::vec3(0, -10, -10.0));
	entity->getComponent<Transform>()->setScale(glm::vec3(0.1, 0.1, 0.1));


	std::shared_ptr<BoxCollider> entityBoxCollider = entity->addComponent<BoxCollider>();
	entityBoxCollider->setSize(glm::vec3(0.5, 0.5, 0.5));
	entityBoxCollider->setOffset(glm::vec3(0.0, 0.2, 0.0));
	entityBoxCollider->setDebugRenderer(true);

	std::shared_ptr<RigidBody> entityRigidBody = entity->addComponent<RigidBody>();
	entityRigidBody->setMass(10.0);




	std::shared_ptr<Entity> freeCam = core->addEntity();
	std::shared_ptr<Renderer> freeCamRenderer = freeCam->addComponent<Renderer>();

	freeCamRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));

	freeCam->getComponent<Transform>()->setPosition(glm::vec3(-4, -12, -13.0));
	freeCam->getComponent<Transform>()->setScale(glm::vec3(2.0, 2.0, 2.0));

	freeCam->addComponent<CameraController>();

	std::shared_ptr<Camera> freeCamCamera = freeCam->addComponent<Camera>();
	freeCamCamera->setFov(100.0);
	freeCamCamera->setPriority(0.0);
	freeCamCamera->setCameraPosition(glm::vec3(0, 3.8, 0));


	SDL_SetRelativeMouseMode(SDL_TRUE);
	core->run();


	return 0;
}

