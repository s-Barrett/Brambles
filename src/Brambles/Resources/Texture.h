
#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{
    struct Renderer;

    /**
     * @brief Represents a texture resource for rendering.
     */
    struct Texture : Resource
    {
        /**
         * @brief Loads the texture resource.
         */
        void onLoad();

        /**
         * @brief Gets the loaded texture.
         * @return A shared pointer to the texture.
         */
        std::shared_ptr<rend::Texture> getTexture()
        {
            return m_texture;
        }

    private:
        friend struct Brambles::Renderer;

        std::shared_ptr<rend::Texture> m_texture;  /**< Shared pointer to the texture */
    };
}
