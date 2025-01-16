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
        SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse to window and hide cursor
        handleMouseInput();
        handleKeyboardInput();
    }

    void CameraController::handleMouseInput()
    {
        float sensitivity = 0.1f;
        float dx, dy;

        // Get mouse movement delta
        getEntity()->getCore()->getInput()->getMousePosition(dx, dy);

        yaw += dx * sensitivity;
        pitch -= dy * sensitivity;

        // Clamp pitch to prevent flipping
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Update camera rotation
        glm::vec3 rotation(pitch, yaw, 0.0f);
        getTransform()->setRotation(rotation);
    }

    void CameraController::handleKeyboardInput()
    {
        auto transform = getTransform();
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();


        // Unlock mouse when Escape is pressed
        if (getEntity()->getCore()->getInput()->isKey(SDLK_ESCAPE))
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }

        // Movement controls
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

        // Sprinting when holding Shift
        if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT))
        {
            movementSpeed = 70.0f; // Increase speed
        }
        else
        {
            movementSpeed = 40.0f; // Normal speed
        }
    }
}
