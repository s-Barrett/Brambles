
#include <GL/glew.h>
#include "Component.h"
#include <rend/rend.h>

namespace Brambles
{
    struct Model;
    struct Texture;

	/**
	 * @brief Handles the rendering of models and textures in the scene using shaders.
	 */
    struct Renderer : Component
    {
        /**
         * @brief Initializes the Renderer.
         * Sets up OpenGL resources and prepares the Renderer for use.
         */
        Renderer();

        /**
         * @brief Sets the texture for the model.
         * @param _texture The texture to be applied to the model.
         */
        void setTexture(std::shared_ptr<Texture> _texture);

        /**
         * @brief Sets the model to be rendered.
         * @param _modelPath The model to be used for rendering.
         */
        void setModel(std::shared_ptr<Model> _model);

        void setSpecularStrength(float _strength) { m_specularStrength = _strength; }

    private:
        /**
         * @brief Renders the model and applies the texture using shaders.
         * This function will be called during each render cycle to draw the model.
         */
        void onRender();

        GLuint programId; ///< Shader program ID used for rendering.
        GLuint vboId; ///< Vertex buffer object ID that holds vertex data.
        GLuint vaoId; ///< Vertex array object ID that encapsulates vertex state.
        GLuint texture; ///< Texture ID used to apply the texture to the model.

        rend::Mesh mesh; ///< Mesh object containing the model's vertex data.
        rend::Shader shader; ///< Shader program used to render the model.

        std::shared_ptr<Texture> m_texture; ///< Shared pointer to the texture applied to the model.
        std::shared_ptr<Model> m_model; ///< Shared pointer to the model being rendered.

        float m_specularStrength = 1.f;
    };
}
