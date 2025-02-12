
#include "../Resource.h"
#include <rend/rend.h>
#include <memory>

namespace Brambles
{
    struct Renderer;

    /**
     * @brief Represents a shader resource for rendering.
     */
    struct Shader : Resource
    {
        /**
         * @brief Loads the shader resource.
         */
        void onLoad();

        /**
         * @brief Gets the loaded shader.
         * @return A shared pointer to the shader.
         */
        std::shared_ptr<rend::Shader> getShader();

    private:
        friend struct Brambles::Renderer;

        std::shared_ptr<rend::Shader> m_shader;  /**< Shared pointer to the shader */
    };
}
