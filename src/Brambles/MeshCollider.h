#ifndef MESHCOLLIDER_H
#define MESHCOLLIDER_H


#include <vector>
#include <glm/glm.hpp>
#include "Component.h"

namespace Brambles {

	struct Model;

	struct MeshCollider : public Component
    {
    public:
        MeshCollider(std::shared_ptr<Model> model);
        ~MeshCollider();

        void setOffset(const glm::vec3& offset);

		glm::vec3 getOffset();

		std::shared_ptr<Model> getModel() { return m_model; }

        bool checkCollision(std::shared_ptr<MeshCollider> other);

        void renderDebug();
        void setDebugRenderer(bool _debugRenderer) { debugRenderer = _debugRenderer; }


    private:
        std::shared_ptr<Model> m_model; // Reference to the model
        glm::vec3 m_offset; // Offset from the entity's position

        std::shared_ptr<Transform> m_transform;


        // Helper functions for collision detection
        bool checkTriangleCollision(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& point) const;
        bool checkMeshCollision(const MeshCollider& other) const;

        bool debugRenderer;
    };

}

#endif // MESHCOLLIDER_H