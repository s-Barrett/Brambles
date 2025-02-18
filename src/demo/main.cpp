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

	mapRenderer->setModel(core->getResources()->load<Model>("../assets/map/170726_mia348_126884_601_100kmesh_OBJ.obj"));

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






	std::shared_ptr<Entity> camera = core->addEntity();
	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();
	camera->getComponent<Camera>()->setFov(90.0);


	

	core->run();


	return 0;
}

