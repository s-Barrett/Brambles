

#include "CameraController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Transform.h"
#include "../Entity.h"
#include "../Input.h"

#include <Windows.h>
#include <iostream>
#include <SDL2/SDL.h>

namespace Brambles
{


    void CameraController::onTick()
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        handleMouseInput();
        handleKeyboardInput();
    }

    void CameraController::handleMouseInput()
    {
        float sensitivity = 0.1f;
        float dx, dy;

        getEntity()->getCore()->getInput()->getMousePosition(dx, dy);

        yaw += dx * sensitivity; // Yaw changes based on horizontal mouse movement
        pitch -= dy * sensitivity; // Pitch changes based on vertical mouse movement

        // Clamp pitch to avoid gimbal lock
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Update the transform's rotation
        glm::vec3 rotation(pitch, yaw, 0.0f);
        getTransform()->setRotation(rotation);
    }


    void CameraController::handleKeyboardInput()
    {
        auto transform = getTransform();

		float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();

		float movementSpeed = 40.0f;

		std::cout << "Time: " << timeDelta << std::endl;

       
        if (getEntity()->getCore()->getInput()->isKey(SDLK_ESCAPE))
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_w)) {
            transform->move(transform->getForward() * movementSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_s)) {
            transform->move(-transform->getForward() * movementSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_a)) {
            transform->move(-transform->getRight() * movementSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_d)) {
            transform->move(transform->getRight() * movementSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_q)) {
            transform->move(-transform->getUp() * movementSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_e)) {
            transform->move(transform->getUp() * movementSpeed * timeDelta);
        }
    }


}


