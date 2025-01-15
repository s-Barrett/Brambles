#include "PlayerController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Gui.h"
#include "../Transform.h"
#include "../Entity.h"
#include "../Component.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Resources/Audio.h"
#include "../Resources/Texture.h"
#include "../Resources.h"
#include "../Input.h"

#include <Windows.h>
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
		getGui()->button(glm::vec2(100, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCube());
		getGui()->button(glm::vec2(300, 120), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCircle());

	}

	void PlayerController::handleKeyboardInput()
	{
		auto transform = getTransform();

		float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();

	
		if (getEntity()->getCore()->getInput()->isKey(SDLK_UP)) 
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
			getTransform()->setPosition(playerStart);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT)) 
		{
			movementSpeed = 60.0f;
		}
		else 
		{
			movementSpeed = 40.0f;
		}
	}
}