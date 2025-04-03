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
        : m_model(model), m_offset(0.0f), debugRenderer(false) {
    }

    void MeshCollider::onRender() {
        renderDebug();
    }

    MeshCollider::~MeshCollider() {
    }

    void MeshCollider::setOffset(const glm::vec3& offset) {
        m_offset = offset;
    }

    glm::vec3 MeshCollider::getOffset() {
        return m_offset;
    }

    std::shared_ptr<Transform> MeshCollider::getTransform() {
        return getEntity()->getComponent<Transform>();
    }

    void MeshCollider::renderDebug() {
        if (!debugRenderer) return;

        auto entity = getEntity();
        if (!entity->hasComponent<DebugRenderer>()) {
            entity->addComponent<DebugRenderer>();
        }

        auto collider = entity->getComponent<MeshCollider>();
        if (collider) {
            entity->getComponent<DebugRenderer>()->drawMeshCollider(collider, glm::vec3(1.0f, 0.0f, 0.0f));
        }
    }
}