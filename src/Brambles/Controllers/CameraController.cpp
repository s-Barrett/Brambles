#include "CameraController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Transform.h"
#include "../Entity.h"
#include "../Resources/Shader.h"
#include "../Component.h"
#include "../RigidBody.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Input.h"

#ifdef _WIN32
  // TODO: Doe we need this?
  #include <Windows.h>
#endif

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

        getEntity()->getCore()->getInput()->getMousePosition(dx, dy);

        yaw += dx * sensitivity; // Ensure yaw rotates in the correct direction
        pitch -= dy * sensitivity;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        auto camera = getEntity()->getComponent<Camera>();
        if (camera)
        {
            camera->setCameraRotation(glm::vec3(pitch, yaw, 0.0f));
        }

        // Ensure the model follows the camera's yaw
        getTransform()->setRotation(glm::vec3(0.0f, -yaw, 0.0f));
    }

    void CameraController::handleKeyboardInput()
    {
        auto transform = getTransform();
        auto rigidBody = getEntity()->getComponent<RigidBody>();
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();
        auto camera = getEntity()->getComponent<Camera>();

        if (getEntity()->getCore()->getInput()->isKey(SDLK_ESCAPE))
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }

        glm::vec3 forward = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)),
            0.0f,
            sin(glm::radians(yaw))
        ));
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

        glm::vec3 movement(0.0f);

        if (getEntity()->getCore()->getInput()->isKey(SDLK_UP)) movement += forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_DOWN)) movement -= forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_LEFT)) movement -= right;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_RIGHT)) movement += right;

        if (glm::length(movement) > 0.0f)
        {
            movement = glm::normalize(movement) * movementSpeed * timeDelta;
            transform->move(movement);
        }
  
    }
}
