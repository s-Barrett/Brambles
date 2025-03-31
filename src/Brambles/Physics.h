#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace Brambles {
    class RigidBody;
    class BoxCollider;
    class MeshCollider;
    class Transform;

    class Physics {
    public:
        Physics();
        void update(float deltaTime);
        void registerRigidBody(std::shared_ptr<RigidBody> rigidBody);
        void registerCollider(std::shared_ptr<BoxCollider> boxCollider);
        void registerMeshCollider(std::shared_ptr<MeshCollider> meshCollider);
        void setGravity(const glm::vec3& gravity);

    private:
        std::vector<std::shared_ptr<RigidBody>> m_rigidBodies;
        std::vector<std::shared_ptr<BoxCollider>> m_boxColliders;
        std::vector<std::shared_ptr<MeshCollider>> m_meshColliders;

        void checkCollisions();
        void checkBoxMeshCollisions();
        void handleCollision(std::shared_ptr<BoxCollider> collider1, std::shared_ptr<BoxCollider> collider2);
        void handleBoxMeshCollision(std::shared_ptr<BoxCollider> box, std::shared_ptr<MeshCollider> mesh);
        bool checkBoxMeshCollision(std::shared_ptr<BoxCollider> box, std::shared_ptr<MeshCollider> mesh, glm::vec3& collisionNormal);
        bool triangleAABBOverlap(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& boxMin, const glm::vec3& boxMax);
        bool pointInAABB(const glm::vec3& point, const glm::vec3& min, const glm::vec3& max);
        void resolveCollisions();
    };
}

#endif // PHYSICS_H