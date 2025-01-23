

#include "rend/Mesh.h"
#include "rend/Shader.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

namespace Brambles
{
    struct BoxCollider;

	/**
	 * @brief Debug renderer for drawing wireframe boxes and box colliders.
	 */
    struct DebugRenderer : public Component
    {
    public:
        /**
         * @brief Draws a wireframe box.
         * @param position Position of the box.
         * @param size Size of the box.
         * @param color Color of the box.
         */
        void drawWireframeBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);

        /**
         * @brief Draws a box collider.
         * @param collider The box collider to draw.
         * @param color Color of the collider.
         */
        void drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color);

    private:
        GLuint programId; ///< Shader program ID.
        GLuint vboId; ///< Vertex buffer object ID.
        GLuint vaoId; ///< Vertex array object ID.

        /**
         * @brief Generates a box mesh.
         * @param size Size of the box mesh.
         * @return A shared pointer to the generated mesh.
         */
        std::shared_ptr<rend::Mesh> generateBoxMesh(const glm::vec3& size);

        std::shared_ptr<rend::Shader> debugShader = std::make_shared<rend::Shader>("../assets/shaders/debug/debug.vert", "../assets/shaders/debug/debug.frag");
    };
}
