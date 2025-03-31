#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "Core.h"
#include "Physics.h"

namespace Brambles {

    RigidBody::RigidBody()
        : m_mass(1.0f), m_velocity(0.0f), m_gravity(0.0f, -200.0f, 0.0f), m_isStatic(false) {}

    void RigidBody::update(float deltaTime) {
        if (m_isStatic)
            return;

        bool grounded = isGrounded();
        if (m_velocity.y > 0)
            grounded = false;

        if (!grounded) {
            m_velocity += m_gravity * deltaTime;

            float airResistance = 0.15f;
            m_velocity.x *= (1.0f - airResistance * deltaTime);
            m_velocity.z *= (1.0f - airResistance * deltaTime);
        }
        else {
            if (m_velocity.y < 0)
                m_velocity.y = 0.0f;

            float floorFriction = 0.98f;
            m_velocity.x *= floorFriction;
            m_velocity.z *= floorFriction;
        }

        getTransform()->setPosition(getTransform()->getPosition() + m_velocity * deltaTime);
    }

    void RigidBody::setMass(float mass) { m_mass = mass; }
    float RigidBody::getMass() const { return m_mass; }

    void RigidBody::setVelocity(const glm::vec3& velocity) { m_velocity = velocity; }
    const glm::vec3& RigidBody::getVelocity() const { return m_velocity; }

    void RigidBody::applyForce(const glm::vec3& force) {
        if (!m_isStatic) {
            m_velocity += force / m_mass;
        }
    }

    bool RigidBody::isGrounded() {
        // Create a small box collider at the bottom of the rigidbody for ground checking
        glm::vec3 checkPos = getTransform()->getPosition() - glm::vec3(0, 0.1f, 0);
        glm::vec3 checkSize(0.5f, 0.05f, 0.5f); // Small flat box for ground detection

        // Get all colliders from the entity's core
        auto core = getEntity()->getCore();
        if (!core) return false;

        auto physics = core->getPhysics();
        if (!physics) return false;

        // Check against all static colliders
        for (auto& entity : core->getEntities()) {
            // Check box colliders
            if (auto boxCollider = entity->getComponent<BoxCollider>()) {
                if (boxCollider->getEntity()->getComponent<RigidBody>() &&
                    !boxCollider->getEntity()->getComponent<RigidBody>()->isStatic()) {
                    continue; // Skip non-static colliders
                }

                // Create temporary AABB for ground check
                glm::vec3 boxPos = boxCollider->getEntity()->getComponent<Transform>()->getPosition() + boxCollider->getOffset();
                glm::vec3 boxSize = boxCollider->getSize();
                glm::vec3 boxMin = boxPos - boxSize * 0.5f;
                glm::vec3 boxMax = boxPos + boxSize * 0.5f;

                // Check if our ground check position is inside this box
                if (checkPos.x >= boxMin.x && checkPos.x <= boxMax.x &&
                    checkPos.z >= boxMin.z && checkPos.z <= boxMax.z &&
                    checkPos.y <= boxMax.y && checkPos.y >= boxMin.y) {
                    return true;
                }
            }

            // Check mesh colliders (simple AABB check)
            if (auto meshCollider = entity->getComponent<MeshCollider>()) {
                if (meshCollider->getEntity()->getComponent<RigidBody>() &&
                    !meshCollider->getEntity()->getComponent<RigidBody>()->isStatic()) {
                    continue; // Skip non-static colliders
                }

                // Simple AABB check against mesh collider bounds
                // Note: For better accuracy, you'd want to check against the actual mesh triangles
                glm::vec3 meshPos = meshCollider->getTransform()->getPosition() + meshCollider->getOffset();
                glm::vec3 meshSize(10.0f, 10.0f, 10.0f); // Approximate size - adjust as needed
                glm::vec3 meshMin = meshPos - meshSize * 0.5f;
                glm::vec3 meshMax = meshPos + meshSize * 0.5f;

                if (checkPos.x >= meshMin.x && checkPos.x <= meshMax.x &&
                    checkPos.z >= meshMin.z && checkPos.z <= meshMax.z &&
                    checkPos.y <= meshMax.y && checkPos.y >= meshMin.y) {
                    return true;
                }
            }
        }

        return false;
    }

    void RigidBody::setGravity(const glm::vec3& gravity) { m_gravity = gravity; }
    const glm::vec3& RigidBody::getGravity() const { return m_gravity; }

    void RigidBody::setStatic(bool isStatic) { m_isStatic = isStatic; }
    bool RigidBody::isStatic() const { return m_isStatic; }
}