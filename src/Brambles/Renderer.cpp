
#include "Renderer.h"
#include "glm/glm.hpp"
#include "Resources/Model.h"
#include "Camera.h"
#include "Core.h"
#include "Transform.h"
#include "Entity.h"

#include "Resources/Texture.h"


namespace Brambles
{

	Renderer::Renderer()
		: shader("../assets/shaders/light/light.vert"
			, "../assets/shaders/light/light.frag")
	{


	}

	void Renderer::setTexture(std::shared_ptr<Texture> _texturePath)
	{
		m_texture = _texturePath;
	}

	void Renderer::setModel(std::shared_ptr<Model> _modelPath)
	{
		m_model = _modelPath;
	}


	void Renderer::onRender()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		auto camera = getEntity()->getCore()->getCamera();
		glm::mat4 perspectiveProjection = camera->getProjectionMatrix();
		glm::mat4 view = camera->getViewMatrix();

		shader.use();
		glBindTexture(GL_TEXTURE_2D, m_texture->m_texture->id());
		shader.uniform("u_View", view);
		shader.uniform("u_Model", getEntity()->getComponent<Transform>()->getModelMatrix());
		shader.uniform("u_Projection", perspectiveProjection);

		glBindVertexArray(m_model->m_model->vao_id());
		glDrawArrays(GL_TRIANGLES, 0, m_model->m_model->vertex_count());
	}


}