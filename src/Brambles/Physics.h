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
        void handleCollision(std::shared_ptr<BoxCollider> boxCollider, std::shared_ptr<MeshCollider> meshCollider);

        std::vector<std::shared_ptr<BoxCollider>>& getBoxColliders() { return m_boxColliders; }
        std::vector<std::shared_ptr<MeshCollider>>& getMeshColliders() { return m_meshColliders; }
    private:
        void checkCollisions();
        void resolveCollisions();

        std::vector<std::shared_ptr<BoxCollider>> m_boxColliders;
        std::vector<std::shared_ptr<MeshCollider>> m_meshColliders;
        std::vector<std::shared_ptr<RigidBody>> m_rigidBodies;
    };
}