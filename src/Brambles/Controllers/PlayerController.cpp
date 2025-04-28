#include "PlayerController.h"
#include "../Core.h"
#include "../Timer.h"
#include "../Entity.h"
#include "../Input.h"
#include "../RigidBody.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../AudioSource.h"
#include "../Sound.h"
#include "../Component.h"
#include "../Resources.h"
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

    void PlayerController::onInitialize()
    {

        yaw = 0.0f; // Default yaw to face along the negative Z axis
        pitch = 0.0f; // Default pitch
        sensitivity = 0.1f;


        // Initialize footstep audio
        footstepAudio = getEntity()->addComponent<AudioSource>();
        auto sound = getEntity()->getCore()->getResources()->load<Sound>("../assets/sounds/halflife/pl_step");

        if (!sound)
        {
            std::cerr << "Failed to load footstep sound!" << std::endl;
            return;
        }

	
        footstepAudio->setSound(sound);
        footstepTimer = 0.0f;
        isMoving = false;
    }

    void PlayerController::handleFootsteps()
    {
        if (!footstepAudio) return;

        auto rigidBody = getEntity()->getComponent<RigidBody>();
        if (!rigidBody) return;

        bool isGrounded = rigidBody->isGrounded;
        glm::vec3 velocity = rigidBody->getVelocity();
        float horizontalSpeed = glm::length(glm::vec3(velocity.x, 0.0f, velocity.z));

        // Only consider moving if we have significant horizontal speed and are grounded
        bool currentlyMoving = isGrounded && (horizontalSpeed > 0.5f);

        float deltaTime = getEntity()->getCore()->getTimer()->getDeltaTime();

        if (currentlyMoving)
        {
            footstepTimer -= deltaTime;

            if (footstepTimer <= 0.0f)
            {
                // Configure audio source properties
                footstepAudio->setLooping(false); // Ensure it's not looping
                footstepAudio->setGain(0.5f);     // Set appropriate volume

                // Play the footstep
                footstepAudio->play();

                // Set interval based on speed
                footstepTimer = (horizontalSpeed > 5.0f) ? 0.35f : 0.45f;
            }
        }
        else
        {
            // Reset timer when not moving
            footstepTimer = 0.0f;
            footstepAudio->stop();
            // Stop the sound if it's playing
            if (footstepAudio->isPlaying())
            {
                footstepAudio->stop();
            }
        }

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
            camera->setCameraRotation(glm::vec3(pitch, yaw, tiltAngle));
        }

        getTransform()->setRotation(glm::vec3(0.0f, -yaw, 0.0f));
    }

    void PlayerController::handleKeyboardInput()
    {
        auto transform = getTransform();
        auto rigidBody = getEntity()->getComponent<RigidBody>();
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();
        auto camera = getEntity()->getComponent<Camera>();
        bool isGrounded = rigidBody->isGrounded;  

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

        // Camera tilt based on movement
        float targetTilt = 0.0f;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_a)) targetTilt = -maxTiltAngle;
        if (getEntity()->getCore()->getInput()->isKey(SDLK_d)) targetTilt = maxTiltAngle;

        // Smoothly interpolate the tilt
        tiltAngle = glm::mix(tiltAngle, targetTilt, tiltSpeed * timeDelta);

        // If no movement input, smoothly return to center
        if (!getEntity()->getCore()->getInput()->isKey(SDLK_a) &&
            !getEntity()->getCore()->getInput()->isKey(SDLK_d))
        {
            tiltAngle = glm::mix(tiltAngle, 0.0f, tiltReturnSpeed * timeDelta);
        }
        if (getEntity()->getCore()->getInput()->isKey(SDLK_LSHIFT) && isGrounded == true) {
            movementSpeed = 20.0f;
            footstepAudio->setGain(10.0f);
			footstepAudio->setPitch(1.1f);  // Increase pitch for sprinting
        }
        else
        {
            footstepAudio->setGain(0.5f);
            footstepAudio->setPitch(1.0f);
			movementSpeed = 10.0f;  // Reset to normal speed when not sprinting
        }

        if (glm::length(input) > 0.0f)
        {
            handleFootsteps();
			targetVelocity = glm::normalize(input) * movementSpeed;
        }

        glm::vec3 currentVelocity = rigidBody->getVelocity();
        glm::vec3 horizontalVelocity = glm::vec3(currentVelocity.x, 0.0f, currentVelocity.z);

    
        horizontalVelocity = glm::mix(horizontalVelocity, targetVelocity, 6.0f * timeDelta);  // Smooth transition
        horizontalVelocity.y = currentVelocity.y;  // Keep y velocity for gravity     
        rigidBody->setVelocity(horizontalVelocity);

        // Jumping logic
        if (getEntity()->getCore()->getInput()->isKey(SDLK_SPACE))  // Press space to jump
        {
            if (isGrounded)
            {
                rigidBody->setVelocity(glm::vec3(currentVelocity.x * 1.2, jumpForce, currentVelocity.z * 1.2));  // Apply jump force
           
            }
        }

        if (getEntity()->getCore()->getInput()->isKey(SDLK_p)) camera->setPriority(+1.0);
        if (getEntity()->getCore()->getInput()->isKey(SDLK_o)) camera->setPriority(-1.0);

     
       
        
    }

}
