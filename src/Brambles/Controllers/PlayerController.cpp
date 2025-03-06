#include "PlayerController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Entity.h"
#include "../Input.h"
#include "../RigidBody.h"
#include "../Transform.h"
#include "../Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SDL2/SDL_keycode.h>

namespace Brambles
{
    void PlayerController::onTick()
    {
        handleMouseInput();
        handleKeyboardInput();
    }

    void PlayerController::handleMouseInput()
    {
        float sensitivity = 0.1f;
        float dx, dy;

        getEntity()->getCore()->getInput()->getMousePosition(dx, dy);

        yaw += dx * sensitivity;
        pitch -= dy * sensitivity;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        auto camera = getEntity()->getComponent<Camera>();
        if (camera)
        {
            camera->setCameraRotation(glm::vec3(pitch, yaw, 0.0f));
        }


        getTransform()->setRotation(glm::vec3(0.0f, -yaw, 0.0f));
    }

    void PlayerController::handleKeyboardInput()
    {
        auto transform = getTransform();
        auto rigidBody = getEntity()->getComponent<RigidBody>();
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();
        auto camera = getEntity()->getComponent<Camera>();

        bool isGrounded = rigidBody->isGrounded();  

        std::cout << "Grounded: " << (isGrounded ? "Yes" : "No") << std::endl;  // Debugging if grounded

        glm::vec3 forward = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)),
            0.0f,
            sin(glm::radians(yaw))
        ));
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

        glm::vec3 input(0.0f);
        glm::vec3 targetVelocity(0.0f);

        // Handle basic input for movement
        if (getEntity()->getCore()->getInput()->isKey(SDLK_w)) input += forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_s)) input -= forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_a)) input -= right;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_d)) input += right;

        if (glm::length(input) > 0.0f)
        {
            input = glm::normalize(input);  
            targetVelocity = input * movementSpeed; 
        }

        glm::vec3 currentVelocity = rigidBody->getVelocity();
        glm::vec3 horizontalVelocity = glm::vec3(currentVelocity.x, 0.0f, currentVelocity.z);

    
        horizontalVelocity = glm::mix(horizontalVelocity, targetVelocity, 10.0f * timeDelta);  // Smooth transition

        horizontalVelocity.y = currentVelocity.y;  // Keep y velocity for gravity

     
        rigidBody->setVelocity(horizontalVelocity);

      
        std::cout << "Velocity: " << rigidBody->getVelocity().x << ", " << rigidBody->getVelocity().y << ", " << rigidBody->getVelocity().z << std::endl;

        // Jumping logic
        if (getEntity()->getCore()->getInput()->isKey(SDLK_SPACE))  // Press space to jump
        {
            if (isGrounded)
            {
                rigidBody->setVelocity(glm::vec3(currentVelocity.x, jumpForce, currentVelocity.z));  // Apply jump force
                std::cout << "Jumping!\n";
            }
        }

        if (getEntity()->getCore()->getInput()->isKey(SDLK_p)) camera->setPriority(+1.0);
        if (getEntity()->getCore()->getInput()->isKey(SDLK_o)) camera->setPriority(-1.0);
    }

}
