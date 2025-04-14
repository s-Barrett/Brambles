#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
#include "Component.h"

namespace Brambles {
	struct RigidBody : public Component {
	public:
		RigidBody();
		void update(float deltaTime);

		void setMass(float mass);
		float getMass() const;

		void setVelocity(const glm::vec3& velocity);
		const glm::vec3& getVelocity() const;

		void applyForce(const glm::vec3& force);
	
		void setIsGrounded(bool grounded) { isGrounded = grounded; }
		bool isGrounded = false;

		void setGravity(const glm::vec3& gravity);
		const glm::vec3& getGravity() const;

		void setStatic(bool isStatic);
		bool isStatic() const;

		void resetFallTime() { m_timeFalling = 0.0f; }
		void addFallTime(float dt) { m_timeFalling += dt; }
		float getFallTime() const { return m_timeFalling; }

	private:

		float m_timeFalling = 0.0f;
		float m_mass;
		glm::vec3 m_velocity;
		glm::vec3 m_gravity;



		bool m_isStatic;
	};
}

#endif // RIGIDBODY_H