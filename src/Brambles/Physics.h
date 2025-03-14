#pragma once

#include <vector>
#include <memory>
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "RigidBody.h"


namespace Brambles 
{

    struct Physics {
    public:
        Physics();
        void update(float deltaTime);

        // Add/remove colliders
        void registerCollider(std::shared_ptr<BoxCollider> boxCollider);
		void registerRigidBody(std::shared_ptr<RigidBody> rigidBody);
		void registerMeshCollider(std::shared_ptr<MeshCollider> meshCollider);


		// Set gravity for all rigidbodies
		void setGravity(const glm::vec3& gravity);

		void handleCollision(std::shared_ptr<BoxCollider> collider1, std::shared_ptr<BoxCollider> collider2);

		std::vector<std::shared_ptr<BoxCollider>>& getBoxColliders() { return m_boxColliders; }
    private:
        // Collision detection functions
        void checkCollisions();
        void resolveCollisions();

        // Collections of all colliders and rigidbodies
        std::vector<std::shared_ptr<BoxCollider>> m_boxColliders;
		std::vector<std::shared_ptr<MeshCollider>> m_meshColliders;
        std::vector<std::shared_ptr<RigidBody>> m_rigidBodies;
    };
}
