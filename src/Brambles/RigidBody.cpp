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

    void RigidBody::collisionResponse(std::shared_ptr<BoxCollider> _collider, std::shared_ptr<BoxCollider>  _other)
    {
        glm::vec3 posA = getTransform()->getPosition();
        glm::vec3 posB = _other->getTransform()->getPosition();

        // Get size (Half-Size)
        glm::vec3 sizeA = _collider->getSize() / 2.0f;
        glm::vec3 sizeB = _other->getSize() / 2.0f;

        // Compute the minimum translation vector (MTV)
        glm::vec3 delta = posA - posB;
        glm::vec3 overlap = glm::vec3(
            sizeA.x + sizeB.x - abs(delta.x),
            sizeA.y + sizeB.y - abs(delta.y),
            sizeA.z + sizeB.z - abs(delta.z)
        );

        if (overlap.x < overlap.y && overlap.x < overlap.z)
        {
            posA.x += (delta.x > 0) ? overlap.x : -overlap.x;
            posB.x += (delta.x > 0) ? -overlap.x : overlap.x;
        }
        else if (overlap.y < overlap.z)
        {
            posA.y += (delta.y > 0) ? overlap.y : -overlap.y;
            posB.y += (delta.y > 0) ? -overlap.y : overlap.y;

            // Stop vertical velocity if colliding with floor (Y axis)
            if (delta.y < 0)  // If moving down (falling)
            {
                m_velocity.y = 0.0f; // Stop downward motion
            }
        }
        else
        {
            posA.z += (delta.z > 0) ? overlap.z : -overlap.z;
            posB.z += (delta.z > 0) ? -overlap.z : overlap.z;
        }
        _other->getTransform()->setPosition(posB);
        getTransform()->setPosition(posA);
    }



    void RigidBody::onTick()
    {
        std::vector<std::shared_ptr<BoxCollider>> boxColliders;
        getEntity()->getCore()->seekComponents(boxColliders);

        for (auto boxCollider : boxColliders)
        {
            if (boxCollider->getTransform() == getTransform())
                continue;
        
            auto myCollider = getEntity()->getComponent<BoxCollider>();
            if (!myCollider) continue;

            if (boxCollider->isColliding(myCollider))
            {
			    collisionResponse(myCollider, boxCollider);
            }


        }

		
        float timeDelta = getEntity()->getCore()->getTimer()->getDeltaTime();

        m_velocity += m_gravity * timeDelta;

        // Update the position based on the velocity
        glm::vec3 newPos = getTransform()->getPosition() + m_velocity * timeDelta;
        getTransform()->setPosition(newPos);

    }

}
