#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "component.h"

namespace Brambles {

    class RigidBody : public Component {
    public:
        RigidBody();

        // Update the rigidbody based on physics
        void update(float deltaTime);

		// Set the static flag
        bool isStatic() const { return m_isStatic; }

        void setStatic(bool isStatic) { m_isStatic = isStatic; }


        void setMass(float mass);

        float getMass() const;

        void setVelocity(const glm::vec3& velocity);

        const glm::vec3& getVelocity() const;

		void setGravity(const glm::vec3& gravity) { m_gravity = gravity; }

		glm::vec3 getGravity() const { return m_gravity; }

        void applyForce(const glm::vec3& force);

		bool isGrounded();

    private:
        float m_mass;
        glm::vec3 m_velocity;
        glm::vec3 m_gravity;
		bool m_isStatic;
    };
}
