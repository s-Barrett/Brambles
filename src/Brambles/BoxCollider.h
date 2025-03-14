#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <glm/glm.hpp>
#include <memory>
#include "Component.h"

namespace Brambles {

    // Forward declaration of RigidBody since we may need it in collision response
    class RigidBody;

	struct BoxCollider : public Component
    {
    public:
        BoxCollider();


        void onRender() override;

        // Set the size of the box collider
        void setSize(const glm::vec3& size);

        // Set the offset of the box collider
        void setOffset(const glm::vec3& offset);

        // Check collision with another BoxCollider (or any other Collider)
        bool checkCollision(std::shared_ptr<BoxCollider> other);

		// Check collision with the ground (used for player collision)
		bool checkCollisionWithGround(const glm::vec3& checkPosition);

        void setDebugRenderer(bool _debugRenderer) { debugRenderer = _debugRenderer; }

		void renderDebug();

        // Getters
        glm::vec3 getSize() const { return m_size; }
        glm::vec3 getOffset() const { return m_offset; }

    private:
        glm::vec3 m_size;    // Size of the box collider
        glm::vec3 m_offset;  // Offset position of the collider relative to the entity

        bool debugRenderer;
    };
}

#endif
