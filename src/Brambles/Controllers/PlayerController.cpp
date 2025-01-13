#include "PlayerController.h"
#include "../Transform.h"
#include "../Entity.h"
#include "../Core.h"
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

	void PlayerController::handleKeyboardInput()
	{
		auto transform = getTransform();

		if (getEntity()->getCore()->getInput()->isKey(SDLK_UP)) 
		{
			transform->move(-transform->getRight() * playerSpeed);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_DOWN)) 
		{
			transform->move(transform->getRight() * playerSpeed);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_LEFT)) 
		{
			transform->move(-transform->getForward() * playerSpeed);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_RIGHT)) 
		{
			transform->move(transform->getForward() * playerSpeed);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_SPACE)) 
		{
			getTransform()->move(playerStart);
		}
		if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT)) 
		{
			playerSpeed = 0.4;
		}
		else 
		{
			playerSpeed = 0.2;
		}
	}
}