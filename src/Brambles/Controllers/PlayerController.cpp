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
	


		if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT))
		{
			getGui()->button(glm::vec2(650, 650), glm::vec2(600, 600), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshStar());//Creates a button this one covers the size of the screen on keypress LSHIFT
		}
		else
		{
			if (getEntity()->getCore()->getInput()->isKey(SDLK_f))
			{
				std::shared_ptr<rend::Shader> orthoShader = std::make_shared<rend::Shader>("../assets/shaders/gui/ortho.vert", "../assets/shaders/gui/ortho.frag"); //loading shaders for the buttons
				getGui()->setGuiShader(orthoShader);
				getGui()->button(glm::vec2(80, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCube());
				getGui()->button(glm::vec2(285, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCircle());
				getGui()->button(glm::vec2(450, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshTriangle());
				getGui()->button(glm::vec2(650, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshStar()); //displaying all button types
			}
			else
			{
				std::shared_ptr<rend::Shader> orthoShader = std::make_shared<rend::Shader>("../assets/shaders/gui/fun.vert", "../assets/shaders/gui/fun.frag");// loading another shader for the buttons
				getGui()->setGuiShader(orthoShader);
				getGui()->button(glm::vec2(80, 100), glm::vec2(100, 100), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCube());
				getGui()->button(glm::vec2(285, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshCircle());
				getGui()->button(glm::vec2(450, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshTriangle());
				getGui()->button(glm::vec2(650, 130), glm::vec2(60, 60), getEntity()->getCore()->getResources()->load<Texture>("../assets/objects/walter/face.png"), getGui()->meshStar());
			}
		}

	}

	void PlayerController::handleKeyboardInput()
	{
		auto transform = getTransform();

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
			getTransform()->setPosition(playerStart);//sets the player back to the start(0, 0, 0)
		}
	}
}
