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

struct CameraController : public Component
{

	void onInitialize()
	{
		
	}
	void onTick()
	{
		float cameraSpeed = 40.0;

		if (getEntity()->getCore()->getInput()->isKey(SDLK_UP))
		{
			std::cout << "Key pressed! Up Arrow" << std::endl;
			move(getTransform()->getForward() * cameraSpeed);
			std::cout << "Position: " << getTransform()->getPosition().x << ", " << getTransform()->getPosition().y << ", " << getTransform()->getPosition().z << std::endl;
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_DOWN))
		{
			std::cout << "Key pressed! Down Arrow" << std::endl;
			move(-getTransform()->getForward() * cameraSpeed);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_LEFT))
		{
			std::cout << "Key pressed! Left Arrow" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(-0.01, 0, 0));
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_RIGHT))
		{
			std::cout << "Key pressed! Right Arrow" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(0.01, 0, 0));
		}
	}
};


struct EntityController : public Component
{
	void onInitialize()
	{
		std::cout << "EntityrController Initialize" << std::endl;
	}
	void onTick()
	{
		if (getEntity()->getCore()->getInput()->isKey(SDLK_w))
		{
			std::cout << "Key pressed! W" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(0, 0, -10.0));
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_s))
		{
			std::cout << "Key pressed! S" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(0, 0, 10.0));
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_a))
		{
			std::cout << "Key pressed! A" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(-10.0, 0, 0));
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_d))
		{
			std::cout << "Key pressed! D" << std::endl;
			getEntity()->getComponent<Transform>()->move(glm::vec3(10.0, 0, 0));
		}
	}
	void tick()
	{
		std::cout << "tick" << std::endl;
	}
};

int main(int argc, char* argv[])
{

	std::shared_ptr<Core> core = Core::initialize();


	std::shared_ptr<Entity> camera = core->addEntity();
	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();


	std::shared_ptr<Entity> entity = core->addEntity();
	entity->addComponent<EntityController>();
	entity->addComponent<Transform>();
	std::shared_ptr<Renderer> entityRender = entity->addComponent<Renderer>();

	entityRender->setTexture(core->getResources()->load<Texture>("../assets/walter/skycull.png"));
	entityRender->setModel(core->getResources()->load<Model>("../assets/walter/walter.obj"));

	std::shared_ptr<AudioSource> sound = entity->addComponent<AudioSource>();

	sound->setSound(core->getResources()->load<Sound>("../assets/sounds/halflife/hellofreeman"));
	sound->play();

	

	core->run();


	return 0;
}

