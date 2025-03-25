#include "Physics.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include <iostream>

namespace Brambles {

    Physics::Physics() {}

    void Physics::update(float deltaTime) {
        for (auto& rigidBody : m_rigidBodies) {
            if (rigidBody->isStatic()) continue; 

            rigidBody->update(deltaTime);

            if (!rigidBody->isGrounded()) {
                glm::vec3 velocity = rigidBody->getVelocity();
                velocity.y - rigidBody->getGravity().y * deltaTime; 
                rigidBody->setVelocity(velocity);
            }

			checkCollisions();
        }
    }

    void Physics::registerRigidBody(std::shared_ptr<RigidBody> rigidBody) {
        m_rigidBodies.push_back(rigidBody);
    }

    void Physics::registerCollider(std::shared_ptr<BoxCollider> boxCollider) {
        m_boxColliders.push_back(boxCollider);
    }

	void Physics::registerMeshCollider(std::shared_ptr<MeshCollider> meshCollider) {
		m_meshColliders.push_back(meshCollider);
	}

    void Physics::setGravity(const glm::vec3& gravity) {
        for (auto& rigidBody : m_rigidBodies) {
            rigidBody->setGravity(gravity);
        }
    }

    void Physics::checkCollisions() {
        for (size_t i = 0; i < m_boxColliders.size(); ++i) {
            for (size_t j = i + 1; j < m_boxColliders.size(); ++j) {
                auto& boxCollider1 = m_boxColliders[i];
                auto& boxCollider2 = m_boxColliders[j];

                if (boxCollider1->getEntity() == boxCollider2->getEntity()) continue;

                if (boxCollider1->checkCollision(boxCollider2)) {

                    handleCollision(boxCollider1, boxCollider2);
                }
            }
        }
    }


    void Physics::handleCollision(std::shared_ptr<BoxCollider> collider1, std::shared_ptr<BoxCollider> collider2) {
        auto entity1 = collider1->getEntity();
        auto entity2 = collider2->getEntity();

        auto rb1 = entity1->getComponent<RigidBody>();
        auto rb2 = entity2->getComponent<RigidBody>();

        bool static1 = (!rb1 || rb1->isStatic());
        bool static2 = (!rb2 || rb2->isStatic());

      
        glm::vec3 pos1 = entity1->getComponent<Transform>()->getPosition();
        glm::vec3 pos2 = entity2->getComponent<Transform>()->getPosition();
        glm::vec3 vel1 = rb1 ? rb1->getVelocity() : glm::vec3(0.0f);
        glm::vec3 vel2 = rb2 ? rb2->getVelocity() : glm::vec3(0.0f);

        glm::vec3 normal = glm::normalize(pos2 - pos1);
        if (glm::length(normal) < 0.0001f) {
            normal = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        glm::vec3 relativeVelocity = vel2 - vel1;
        float velocityAlongNormal = glm::dot(relativeVelocity, normal);

        if (velocityAlongNormal > 0) return;

   
        if (static1 || static2) {
          
            if (!static1 && static2) {
                // Only object 1 is dynamic.
                float mass1 = rb1->getMass();
             
                float impulseScalar = -(1.0f + 0.0f) * velocityAlongNormal;
                glm::vec3 impulse = impulseScalar * normal;
                rb1->setVelocity(vel1 - impulse / mass1);
            }
            else if (static1 && !static2) {
                float mass2 = rb2->getMass();
                float impulseScalar = -(1.0f + 0.0f) * velocityAlongNormal;
                glm::vec3 impulse = impulseScalar * normal;
                rb2->setVelocity(vel2 + impulse / mass2);
            }
           
            return;
        }

     
        float mass1 = rb1->getMass();
        float mass2 = rb2->getMass();
        float invMass1 = 1.0f / mass1;
        float invMass2 = 1.0f / mass2;

       
        float restitution = 0.0f;
        float impulseScalar = -(1 + restitution) * velocityAlongNormal / (invMass1 + invMass2);
        glm::vec3 impulse = impulseScalar * normal;
        rb1->setVelocity(vel1 - impulse * invMass1);
        rb2->setVelocity(vel2 + impulse * invMass2);

        // Friction impulse calculation
        glm::vec3 newRelativeVelocity = rb2->getVelocity() - rb1->getVelocity();
        glm::vec3 tangent = newRelativeVelocity - glm::dot(newRelativeVelocity, normal) * normal;
        if (glm::length(tangent) > 0.001f) {
            tangent = glm::normalize(tangent);
     
            float jt = -glm::dot(newRelativeVelocity, tangent) / (invMass1 + invMass2);
         
            float mu = 1.0f;
            jt = glm::clamp(jt, -mu * impulseScalar, mu * impulseScalar);
            glm::vec3 frictionImpulse = jt * tangent;
            rb1->setVelocity(rb1->getVelocity() - frictionImpulse * invMass1);
            rb2->setVelocity(rb2->getVelocity() + frictionImpulse * invMass2);
        }
    }



    void Physics::resolveCollisions() {
        for (auto& collider : m_boxColliders) {
            for (auto& otherCollider : m_boxColliders) {
                if (collider == otherCollider) continue;

                if (collider->checkCollision(otherCollider)) {
                    auto transform = collider->getEntity()->getComponent<Transform>();
                    glm::vec3 direction = glm::normalize(transform->getPosition() - otherCollider->getEntity()->getComponent<Transform>()->getPosition());
                    float overlap = (collider->getSize().y + otherCollider->getSize().y) * 0.5f;

                    transform->setPosition(transform->getPosition() + direction * overlap);
                }
            }
        }
    }

}
