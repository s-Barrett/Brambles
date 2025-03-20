#include "MeshCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Resources/Model.h"
#include "Entity.h"
#include "RigidBody.h"
#include "DebugRenderer.h"
#include <iostream>

namespace Brambles {

    MeshCollider::MeshCollider(std::shared_ptr<Model> model)
        : m_model(model), m_offset(0.0f) {
        
    }

    void MeshCollider::onRender()
    {
        renderDebug();
    }

    MeshCollider::~MeshCollider() {
        // Clean up if necessary
    }

    void MeshCollider::setOffset(const glm::vec3& offset) {
        m_offset = offset;
    }

    glm::vec3 MeshCollider::getOffset() {
        return m_offset;
    }

    bool MeshCollider::checkCollision(std::shared_ptr<MeshCollider> other) {
        return checkMeshCollision(*other);
    }

    void MeshCollider::renderDebug() {
        if (!debugRenderer) return;

        auto entity = getEntity();
        if (!entity->hasComponent<DebugRenderer>()) {
            entity->addComponent<DebugRenderer>();
        }

        auto collider = entity->getComponent<MeshCollider>();
        if (collider) {
            entity->getComponent<DebugRenderer>()->drawMeshCollider(collider, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

    bool MeshCollider::checkTriangleCollision(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& point) const {
        // Implement triangle-point collision detection
        glm::vec3 edge0 = v1 - v0;
        glm::vec3 edge1 = v2 - v0;
        glm::vec3 normal = glm::cross(edge0, edge1);

        float area = glm::length(normal);
        if (area < 0.0001f) return false; // Degenerate triangle

        normal = glm::normalize(normal);

        // Barycentric coordinates
        glm::vec3 vp = point - v0;
        float d = glm::dot(vp, normal);
        if (abs(d) > 0.0001f) return false; // Point not on the triangle's plane

        glm::vec3 cross0 = glm::cross(edge0, vp);
        glm::vec3 cross1 = glm::cross(vp, edge1);

        float u = glm::dot(cross0, normal) / area;
        float v = glm::dot(cross1, normal) / area;

        return (u >= 0.0f && v >= 0.0f && (u + v) <= 1.0f);
    }

    bool MeshCollider::checkMeshCollision(const MeshCollider& other) const {
        if (!m_transform || !other.m_transform) {
            std::cerr << "MeshCollider: Missing Transform component!" << std::endl;
            return false;
        }

        glm::vec3 thisPos = m_transform->getPosition() + m_offset;
        glm::vec3 otherPos = other.m_transform->getPosition() + other.m_offset;


        // Get faces from the model
        const auto& facesThis = m_model->getFaces();
        const auto& facesOther = other.m_model->getFaces();

        // Iterate through all triangles in this mesh
        for (const auto& face : facesThis) {
            glm::vec3 v0 = face.a.position + thisPos; // Use face.a.position
            glm::vec3 v1 = face.b.position + thisPos; // Use face.b.position
            glm::vec3 v2 = face.c.position + thisPos; // Use face.c.position

            // Iterate through all triangles in the other mesh
            for (const auto& otherFace : facesOther) {
                glm::vec3 ov0 = otherFace.a.position + otherPos; // Use otherFace.a.position
                glm::vec3 ov1 = otherFace.b.position + otherPos; // Use otherFace.b.position
                glm::vec3 ov2 = otherFace.c.position + otherPos; // Use otherFace.c.position

                // Check for triangle-triangle intersection (placeholder)
                // Implement a proper triangle-triangle intersection test here
                if (checkTriangleCollision(v0, v1, v2, ov0) ||
                    checkTriangleCollision(v0, v1, v2, ov1) ||
                    checkTriangleCollision(v0, v1, v2, ov2)) {
                    return true;
                }
            }
        }

        return false;
    }

}