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
	


		if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT))
		{
			getGui()->button(glm::vec2(650, 650), glm::vec2(600, 600), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshStar());
		}
		else
		{
			if (getEntity()->getCore()->getInput()->isKey(SDLK_f))
			{
				std::shared_ptr<rend::Shader> orthoShader = std::make_shared<rend::Shader>("../assets/shaders/Gui/ortho.vert", "../assets/shaders/Gui/ortho.frag");
				getGui()->setGuiShader(orthoShader);
				getGui()->button(glm::vec2(100, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCube());
			}
			else
			{
				std::shared_ptr<rend::Shader> orthoShader = std::make_shared<rend::Shader>("../assets/shaders/Gui/fun.vert", "../assets/shaders/Gui/fun.frag");
				getGui()->setGuiShader(orthoShader);
				getGui()->button(glm::vec2(100, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCube());
			}
		}

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
	}
}