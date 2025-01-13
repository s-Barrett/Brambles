#ifndef DEBUG_RENDERER_H
#define DEBUG_RENDERER_H

#include "rend/Mesh.h"
#include <glm/glm.hpp>
#include <memory>

namespace Brambles
{
	struct BoxCollider;
	struct DebugRenderer
    {
    public:

        static void drawWireframeBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);
        static void drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color);

    private:
        static std::shared_ptr<rend::Mesh> generateBoxMesh(const glm::vec3& size);
    };
}

#endif
