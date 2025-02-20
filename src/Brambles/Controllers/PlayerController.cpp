#include "PlayerController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Gui.h"
#include "../Transform.h"
#include "../Entity.h"
#include "../Resources/Shader.h"
#include "../Component.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Resources/Audio.h"
#include "../Resources/Texture.h"
#include "../Resources.h"
#include "../Input.h"
#include "../BoxCollider.h"
#include "../RigidBody.h"

#ifdef _WIN32
  #include <Windows.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>


namespace Brambles
{

	void PlayerController::onTick()
	{
		handleKeyboardInput();

	}

	void PlayerController::onGui()
	{
		std::shared_ptr<Brambles::Shader> orthoShader = getEntity()->getCore()->getResources()->load<Brambles::Shader>("../assets/shaders/gui/ortho");
		getGui()->setGuiShader(orthoShader->getShader());
		getGui()->button(glm::vec2(80, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/gui/health.png"), getGui()->meshCube());
		
	}

	void PlayerController::handleKeyboardInput()
	{
		auto transform = getTransform();
		auto rigidBody = getEntity()->getComponent<RigidBody>();

		float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();//gets the time delta

	
		if (getEntity()->getCore()->getInput()->isKey(SDLK_UP)) //checks key presses
		{
			transform->move(-transform->getRight() * movementSpeed * timeDelta);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_DOWN)) 
		{
			transform->move(transform->getRight() * movementSpeed * timeDelta);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_LEFT)) 
		{
			transform->move(-transform->getForward() * movementSpeed * timeDelta);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_RIGHT)) 
		{
			transform->move(transform->getForward() * movementSpeed * timeDelta);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_SPACE)) 
		{
			transform->move(transform->getUp() * movementSpeed * timeDelta);//sets the player back to the start(0, 0, 0)
			rigidBody->setVelocity(glm::vec3(0.0f, -10.0f, 0.0f));
		}
	}
}
