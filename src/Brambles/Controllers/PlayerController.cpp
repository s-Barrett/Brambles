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
#include "../Sound.h"
#include "../Resources/Audio.h"
#include "../Resources/Model.h"
#include "../Resources/Texture.h"
#include "../Resources.h"
#include "../Input.h"
#include "../BoxCollider.h"
#include "../RigidBody.h"

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

        // Ensure the model follows the camera's yaw
        getTransform()->setRotation(glm::vec3(0.0f, -yaw, 0.0f));
    }

    void PlayerController::handleKeyboardInput()
    {
        auto transform = getTransform();
        auto rigidBody = getEntity()->getComponent<RigidBody>();
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();
        auto camera = getEntity()->getComponent<Camera>();

        bool isGrounded = rigidBody->isGrounded(); // Get actual grounded state

        glm::vec3 forward = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)),
            0.0f,
            sin(glm::radians(yaw))
        ));
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

        glm::vec3 input(0.0f);
        glm::vec3 targetVelocity(0.0f);

        // Further enhanced movement settings for freedom and speed
        float acceleration = isGrounded ? 100.0f : 40.0f; // Faster acceleration, especially in the air
        float airControl = isGrounded ? 1.0f : 6.0f; // More air control for freedom
        float friction = isGrounded ? 1.0f : 0.10f; // Low friction for sliding and control
        float maxSpeed = isGrounded ? movementSpeed * 1.5f : movementSpeed * 1.2f; // Faster overall speed

        static int airJumps = 1; // Allows one extra jump in the air

        // Input handling
        if (getEntity()->getCore()->getInput()->isKey(SDLK_w)) input += forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_s)) input -= forward;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_a)) input -= right;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_d)) input += right;

        if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT) && isGrounded)
        {
            maxSpeed *= 1.8f; // Sprinting speed boost
        }

        glm::vec3 currentVelocity = rigidBody->getVelocity();
        glm::vec3 horizontalVelocity = glm::vec3(currentVelocity.x, 0.0f, currentVelocity.z);

        if (isGrounded)
        {
          
            if (glm::length(input) > 0.0f)
            {
                input = glm::normalize(input);
                targetVelocity = input * maxSpeed;
            }

            // Slidy movement: Interpolate velocity with reduced friction
            horizontalVelocity = glm::mix(horizontalVelocity, targetVelocity, acceleration * timeDelta);

            if (glm::length(input) == 0.0f)
            {
                horizontalVelocity *= 1.0f - (friction * timeDelta); // Low friction for sliding
            }

            airJumps = 1; // Reset air jumps when landing
        }
        else
        {
            if (glm::length(input) > 0.0f)
            {
                input = glm::normalize(input);
                glm::vec3 wishDir = input;

                float wishSpeed = maxSpeed * airControl;
                float currentSpeed = glm::dot(horizontalVelocity, wishDir);
                float addSpeed = wishSpeed - currentSpeed;

                if (addSpeed > 0.0f)
                {
                    horizontalVelocity += wishDir * addSpeed * timeDelta;
                }

                // Air strafing: Full freedom to move while airborne
                horizontalVelocity.x += wishDir.x * addSpeed * 0.99f * timeDelta; // Increased strafing in air
                horizontalVelocity.z += wishDir.z * addSpeed * 0.99f * timeDelta; // Increased strafing in air
            }
        }

        horizontalVelocity.y = currentVelocity.y;
        rigidBody->setVelocity(horizontalVelocity);

        // **Jumping**
        if (getEntity()->getCore()->getInput()->isKey(SDLK_SPACE)) // Ensure it's one-time press
        {
            if (isGrounded)
            {
                rigidBody->setVelocity(glm::vec3(currentVelocity.x, jumpForce, currentVelocity.z));
                std::cout << "Jumping from ground\n";
            }
            else if (airJumps > 1) // Allow air jumps
            {
                rigidBody->setVelocity(glm::vec3(currentVelocity.x, jumpForce * 0.8f, currentVelocity.z));
                airJumps--;
                std::cout << "Air Jump!\n";
            }
        }

        if (getEntity()->getCore()->getInput()->isKey(SDLK_p)) camera->setPriority(+1.0);
        if (getEntity()->getCore()->getInput()->isKey(SDLK_o)) camera->setPriority(-1.0);
    }

}
