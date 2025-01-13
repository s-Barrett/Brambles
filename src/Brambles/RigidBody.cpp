#include "RigidBody.h"
#include "Transform.h"
#include "DebugRenderer.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "Core.h"

#include <vector>
#include <iostream>

namespace Brambles
{
    void RigidBody::renderDebug()
    {
        // Assuming the RigidBody has a BoxCollider attached
        auto collider = getEntity()->getComponent<BoxCollider>();
        if (collider)
        {
            DebugRenderer::drawBoxCollider(collider, glm::vec3(1.0f, 0.0f, 0.0f)); // Red for colliders
        }
    }


    void RigidBody::onTick()
    {
        std::vector<std::shared_ptr<BoxCollider>> colliders;
        getEntity()->getCore()->seekComponents(colliders);

        auto boxCollider = getEntity()->getComponent<BoxCollider>();

        for (const auto& collider : colliders)
        {
            if (collider->getTransform() == getTransform())
            {
                continue;
            }
            if (collider->isColliding(boxCollider))
            {
                float amount = 0.001f;
                const float step = 0.001f;

                while (collider->isColliding(boxCollider))
                {
                    glm::vec3 directions[] = {
                        { amount, 0, 0 }, { -amount, 0, 0 },
                        { 0, 0, amount }, { 0, 0, -amount },
                        { 0, amount, 0 }, { 0, -amount, 0 }
                    };

                    bool resolved = false;

                    for (const auto& dir : directions)
                    {
                        setPosition(getPosition() + dir);
                        if (!collider->isColliding(boxCollider))
                        {
                            resolved = true;
                            break;
                        }
                        setPosition(getPosition() - dir);
                    }

                    if (resolved) break;

                    amount += step;
                }
            }
        }
    }
}
