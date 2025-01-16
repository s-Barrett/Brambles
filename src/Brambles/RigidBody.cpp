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
		glm::vec3 posA = getTransform()->getPosition(); // Get the position of the collider
		glm::vec3 posB = _other->getTransform()->getPosition(); // Get the position of the other collider

        glm::vec3 sizeA = _collider->getSize() / 2.0f;
        glm::vec3 sizeB = _other->getSize() / 2.0f;

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


            if (delta.y < 0)  
            {
				m_velocity.y = 0.0f; 
            }
        }
        else
        {
            posA.z += (delta.z > 0) ? overlap.z : -overlap.z;
			posB.z += (delta.z > 0) ? -overlap.z : overlap.z;// This pushes the rigid body back
        }
        _other->getTransform()->setPosition(posB);
        getTransform()->setPosition(posA);
    }



    void RigidBody::onTick()
    {
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

        m_velocity += m_gravity * timeDelta;// Adding grav but is set to 0 right now

        glm::vec3 newPos = getTransform()->getPosition() + m_velocity * timeDelta;
        getTransform()->setPosition(newPos);

    }

}
