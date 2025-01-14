
#include "rend/Mesh.h"
#include "rend/Shader.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

namespace Brambles
{
	struct BoxCollider;
	struct DebugRenderer : public Component
    {
    public:

		DebugRenderer();

        void drawWireframeBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);
        void drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color);

    private:
        GLuint programId;
        GLuint vboId;
        GLuint vaoId;

        std::shared_ptr<rend::Mesh> generateBoxMesh(const glm::vec3& size);
        rend::Shader debugShader;
    };
}
