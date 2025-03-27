#ifndef MESHCOLLIDER_H
#define MESHCOLLIDER_H

#include <vector>
#include <glm/glm.hpp>
#include "Component.h"

namespace Brambles {
    struct Model;
    struct Transform;

    struct MeshCollider : public Component {
    public:
        MeshCollider(std::shared_ptr<Model> model);
        ~MeshCollider();

        void setOffset(const glm::vec3& offset);
        glm::vec3 getOffset();
        std::shared_ptr<Model> getModel() { return m_model; }
        std::shared_ptr<Transform> getTransform();

        void renderDebug();
        void setDebugRenderer(bool _debugRenderer) { debugRenderer = _debugRenderer; }
        void onRender();

    private:
        std::shared_ptr<Model> m_model;
        glm::vec3 m_offset;
        bool debugRenderer;
    };
}

#endif // MESHCOLLIDER_H