#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "Core.h"
#include "Physics.h"

namespace Brambles {

    RigidBody::RigidBody()
        : m_mass(1.0f), m_velocity(0.0f), m_gravity(0.0f, -20.8f, 0.0f), m_isStatic(false) {}

    void RigidBody::update(float deltaTime) {
        if (m_isStatic)
            return;

        bool grounded = isGrounded;
        if (m_velocity.y > 0)
            grounded = false;

        if (!grounded) {
            m_velocity += m_gravity * deltaTime;

            float airResistance = 3.0f;
            m_velocity.x *= (1.0f - airResistance * deltaTime);
            m_velocity.z *= (1.0f - airResistance * deltaTime);
        }
        else {
            if (m_velocity.y < 0)
                m_velocity.y = 0.0f;

            float floorFriction = 0.96f;
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


    void RigidBody::setGravity(const glm::vec3& gravity) { m_gravity = gravity; }
    const glm::vec3& RigidBody::getGravity() const { return m_gravity; }

    void RigidBody::setStatic(bool isStatic) { m_isStatic = isStatic; }
    bool RigidBody::isStatic() const { return m_isStatic; }
}