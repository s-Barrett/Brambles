#include "Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
    struct BoxCollider;
    struct RigidBody : public Component
    {
        RigidBody() {} 
        ~RigidBody() {}

        void onTick();
		void collisionResponse(std::shared_ptr<BoxCollider> _collider, std::shared_ptr<BoxCollider> _other);

        void setMass(float _mass) { m_mass = _mass; }
        float getMass() const { return m_mass; }

        void setVelocity(const glm::vec3& _velocity) { m_velocity = _velocity; }
        glm::vec3 getVelocity() const { return m_velocity; }

    private:


        //const glm::vec3 m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);
		const glm::vec3 m_gravity = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec3 m_velocity = glm::vec3(0.0f);
        float m_mass = 10.0f;
    };
}
