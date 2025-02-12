#include "RigidBody.h"
#include "Core.h"
#include "Timer.h"
#include "Gui.h"
#include "Transform.h"
#include "Entity.h"
#include "Component.h"
#include "Window.h"
#include "Camera.h"
#include "Resources/Audio.h"
#include "Resources/Texture.h"
#include "Resources.h"
#include "Input.h"
#include "BoxCollider.h"

#include <vector>
#include <iostream>

namespace Brambles
{
   

    void RigidBody::collisionResponse(std::shared_ptr<BoxCollider> _collider, std::shared_ptr<BoxCollider> _other)
    {
        // Get positions of both colliders
        glm::vec3 posA = getTransform()->getPosition() + _collider->getOffset();
        glm::vec3 posB = _other->getTransform()->getPosition() + _other->getOffset();

        // Get half-sizes of both colliders
        glm::vec3 sizeA = _collider->getSize() / 2.0f;
        glm::vec3 sizeB = _other->getSize() / 2.0f;

        // Calculate the overlap between the two colliders
        glm::vec3 delta = posA - posB;
        glm::vec3 overlap = glm::vec3(
            sizeA.x + sizeB.x - abs(delta.x),
            sizeA.y + sizeB.y - abs(delta.y),
            sizeA.z + sizeB.z - abs(delta.z)
        );

        // Get the masses of the two objects
        float massA = getMass();
        float massB = _other->getEntity()->getComponent<RigidBody>()->getMass();

        // Calculate the ratio of mass distribution
        float totalMass = massA + massB;
        float ratioA = massB / totalMass; // How much object A should move
        float ratioB = massA / totalMass; // How much object B should move

        // Determine the minimum overlap axis (x, y, or z)
        if (overlap.x < overlap.y && overlap.x < overlap.z)
        {
            // Resolve collision on the X axis
            if (!_other->getEntity()->getComponent<RigidBody>()->getIsStatic())
            {
                // Move both objects based on their mass ratios
                posA.x += (delta.x > 0) ? overlap.x * ratioA : -overlap.x * ratioA;
                posB.x += (delta.x > 0) ? -overlap.x * ratioB : overlap.x * ratioB;

                // Update positions
                getTransform()->setPosition(posA - _collider->getOffset());
                _other->getTransform()->setPosition(posB - _other->getOffset());
            }
        }
        else if (overlap.y < overlap.z)
        {
            // Resolve collision on the Y axis
            if (!_other->getEntity()->getComponent<RigidBody>()->getIsStatic())
            {
                // Move both objects based on their mass ratios
                posA.y += (delta.y > 0) ? overlap.y * ratioA : -overlap.y * ratioA;
                posB.y += (delta.y > 0) ? -overlap.y * ratioB : overlap.y * ratioB;

                // Update positions
                getTransform()->setPosition(posA - _collider->getOffset());
                _other->getTransform()->setPosition(posB - _other->getOffset());

                // Stop vertical velocity if colliding from above
                if (delta.y < 0)
                {
                    m_velocity.y = 0.0f;
                }
            }
        }
        else
        {
            // Resolve collision on the Z axis
            if (!_other->getEntity()->getComponent<RigidBody>()->getIsStatic())
            {
                // Move both objects based on their mass ratios
                posA.z += (delta.z > 0) ? overlap.z * ratioA : -overlap.z * ratioA;
                posB.z += (delta.z > 0) ? -overlap.z * ratioB : overlap.z * ratioB;

                // Update positions
                getTransform()->setPosition(posA - _collider->getOffset());
                _other->getTransform()->setPosition(posB - _other->getOffset());
            }
        }
    }



    void RigidBody::onTick()
    {

        if (m_isStatic == true)
        {
            getTransform()->setPosition(getPosition());
            m_gravity = glm::vec3(0.0f, 0.0f, 0.0f); // Setting gravity to 0
			m_velocity = glm::vec3(0.0f, 0.0f, 0.0f); // Setting velocity to 0
		}
        else
        {
            m_gravity = glm::vec3(0.0f, -9.8f, 0.0f); // Setting gravity to defult
        }

        std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getEntity()->getCore()->seekComponents(boxColliders);// Seeking all the box colliders

        for (auto boxCollider : boxColliders)
        {
			if (boxCollider->getTransform() == getTransform())// If the box collider is self, skip
                continue;
        
			auto myCollider = getEntity()->getComponent<BoxCollider>();// If the other box collider is self, skip
            if (!myCollider) continue;

			if (boxCollider->isColliding(myCollider))// If the box colliders are colliding
            {
				collisionResponse(myCollider, boxCollider);// Call the collision response
            }


        }

		
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();

        m_velocity += m_gravity * timeDelta;// Adding grav

        glm::vec3 newPos = getTransform()->getPosition() + m_velocity * timeDelta;
        getTransform()->setPosition(newPos);

    }

}
