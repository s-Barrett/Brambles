
#include "Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
    struct BoxCollider;

    /**
     * @brief Represents a RigidBody.
     */
    struct RigidBody : public Component
    {
        RigidBody() {}
        ~RigidBody() {}

        /**
         * @brief Updates physics each frame.
         */
        void onTick();

        /**
         * @brief Handles collision response between colliders.
         * @param _collider First collider.
         * @param _other Second collider.
         */
        void collisionResponse(std::shared_ptr<BoxCollider> _collider, std::shared_ptr<BoxCollider> _other);

        /**
         * @brief Sets the rigid body's mass.
         * @param _mass Mass to set.
         */
        void setMass(float _mass) { m_mass = _mass; }

        /**
         * @brief Gets the rigid body's mass.
         * @return The mass.
         */
        float getMass() const { return m_mass; }

        /**
         * @brief Sets the rigid body's velocity.
         * @param _velocity Velocity to set.
         */
        void setVelocity(const glm::vec3& _velocity) { m_velocity = _velocity; }

        /**
         * @brief Gets the rigid body's velocity.
         * @return The velocity.
         */
        glm::vec3 getVelocity() const { return m_velocity; }

		void setIsStatic(bool _isStatic) { m_isStatic = _isStatic; }

		bool getIsStatic() const { return m_isStatic; }

    private:
        bool m_isGrounded = false; // Flag to track if the object is grounded
		bool m_isStatic = false;
        glm::vec3 m_gravity = glm::vec3(0.0f, 9.8f, 0.0f);
        glm::vec3 m_velocity = glm::vec3(0.0f);
        float m_mass = 1.0f;
    };
}
