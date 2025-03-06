#include "BoxCollider.h"
#include "Transform.h"
#include "Entity.h"
#include "RigidBody.h"
#include "DebugRenderer.h"
#include <iostream>

namespace Brambles {

    BoxCollider::BoxCollider() : m_size(1.0f), m_offset(0.0f) {}

    void BoxCollider::onRender() {
        renderDebug();
    }

    void BoxCollider::setSize(const glm::vec3& size) { m_size = size; }
    void BoxCollider::setOffset(const glm::vec3& offset) { m_offset = offset; }

    void BoxCollider::renderDebug() {
        if (!debugRenderer) return;

        auto entity = getEntity();
        if (!entity->hasComponent<DebugRenderer>()) {
            entity->addComponent<DebugRenderer>();
        }

        auto collider = entity->getComponent<BoxCollider>();
        if (collider) {
            entity->getComponent<DebugRenderer>()->drawBoxCollider(collider, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

    bool BoxCollider::checkCollision(std::shared_ptr<BoxCollider> other) {
        auto transformThis = getEntity()->getComponent<Transform>();
        auto transformOther = other->getEntity()->getComponent<Transform>();

        glm::vec3 thisPos = transformThis->getPosition();
        glm::vec3 otherPos = transformOther->getPosition();

   
        glm::vec3 thisMin = thisPos + m_offset - m_size * 0.5f;
        glm::vec3 thisMax = thisMin + m_size;

        glm::vec3 otherMin = otherPos + other->m_offset - other->m_size * 0.5f;
        glm::vec3 otherMax = otherMin + other->m_size;


        std::cout << "Collider 1: Min(" << thisMin.x << ", " << thisMin.y << ", " << thisMin.z
            << ") Max(" << thisMax.x << ", " << thisMax.y << ", " << thisMax.z << ")\n";
        std::cout << "Collider 2: Min(" << otherMin.x << ", " << otherMin.y << ", " << otherMin.z
            << ") Max(" << otherMax.x << ", " << otherMax.y << ", " << otherMax.z << ")\n";

        bool colliding = (thisMin.x <= otherMax.x && thisMax.x >= otherMin.x) &&
            (thisMin.y <= otherMax.y && thisMax.y >= otherMin.y) &&
            (thisMin.z <= otherMax.z && thisMax.z >= otherMin.z);

        std::cout << "Collision detected: " << (colliding ? "true" : "false") << std::endl;
        return colliding;
    }



    bool BoxCollider::checkCollisionWithGround(const glm::vec3& checkPosition) {
        auto rigidBody = getEntity()->getComponent<RigidBody>();
        if (!rigidBody || !rigidBody->isStatic()) return false;

        glm::vec3 thisPos = getEntity()->getComponent<Transform>()->getPosition() + m_offset;
        glm::vec3 thisSize = m_size;

        return (abs(thisPos.x - checkPosition.x) <= thisSize.x / 2) &&
            (abs(thisPos.y - checkPosition.y) <= thisSize.y / 2) &&
            (abs(thisPos.z - checkPosition.z) <= thisSize.z / 2);
    }

}
