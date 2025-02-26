
#include "Renderer.h"
#include "glm/glm.hpp"
#include "Resources/Model.h"
#include "Camera.h"
#include "Core.h"
#include "Transform.h"
#include "LightManager.h"
#include "Entity.h"

#include "Resources/Texture.h"


namespace Brambles
{

	Renderer::Renderer()
		: shader("../assets/shaders/light/light.vert"
			, "../assets/shaders/light/light.frag")
	{


	}

	void Renderer::setTexture(std::shared_ptr<Texture> _texturePath)//Set the texture  
	{
		m_texture = _texturePath;
	}

	void Renderer::setModel(std::shared_ptr<Model> _modelPath)//Set the model
	{
		m_model = _modelPath;
	}

    void Renderer::onRender() {
        glEnable(GL_DEPTH_TEST);

        // Bind the shader program
        shader.use();

        std::shared_ptr<Core> core = getEntity()->getCore();


        std::vector<std::shared_ptr<Light>> lights = core->getLightManager()->getLights();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> colors;
        std::vector<float> strengths;

        for (const auto& light : lights)
        {
            positions.push_back(light->position);
            colors.push_back(light->colour);
            strengths.push_back(light->strength);
        }

        // Set up camera matrices
        auto camera = getEntity()->getCore()->getCamera();
        glm::mat4 perspectiveProjection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();

        shader.uniform("u_View", view);
        shader.uniform("u_Model", getEntity()->getComponent<Transform>()->getModelMatrix());
        shader.uniform("u_Projection", perspectiveProjection);

        shader.uniform("u_LightPositions", positions);
        shader.uniform("u_LightColors", colors);
        shader.uniform("u_LightStrengths", strengths);

        shader.uniform("u_Ambient", core->getLightManager()->getAmbient());
        shader.uniform("u_SpecStrength", m_specularStrength);


        // Bind the model's VAO
        glBindVertexArray(m_model->m_model->vao_id());

        for (size_t i = 0; i < m_model->getMaterials().size(); ++i) {
            const auto& material = m_model->getMaterials()[i];

            if (material.diffuseTextureID != 0) {
                glBindTexture(GL_TEXTURE_2D, material.diffuseTextureID);
            }
            else {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            size_t vertexCount = 0;
            size_t startIndex = -1;

            // Find faces for the current material
            for (size_t j = 0; j < m_model->getFaces().size(); ++j) {
                const auto& face = m_model->getFaces()[j];
                if (face.materialIndex == i) {
                    if (startIndex == -1) {
                        startIndex = face.startIndex;  // Set starting index
                    }
                    vertexCount += 3; // Each face has 3 vertices
                }
            }



            if (vertexCount > 0) {
                glDrawArrays(GL_TRIANGLES, startIndex, vertexCount);
            }
        }


        // Unbind the VAO
        glBindVertexArray(0);
    }



}