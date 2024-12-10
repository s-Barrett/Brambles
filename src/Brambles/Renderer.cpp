
#include "Renderer.h"
#include "glm/glm.hpp"
#include "Resources/Model.h"
#include "Transform.h"
#include "Entity.h"

#include "Resources/Texture.h"


namespace Brambles
{

	Renderer::Renderer()
		: shader("../assets/shaders/lightvert.glsl"
			, "../assets/shaders/lightfrag.glsl")
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


		glm::mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), (float)700 / (float)700, 0.1f, 500.f);

		//prepare view matrix
		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0, 0.5, -6.0f));
		view = glm::rotate(view, glm::radians(0.0f), glm::vec3(0, 1, 0));
		view = glm::rotate(view, glm::radians(0.0f), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(0.0f), glm::vec3(0, 0, 1));
		view = glm::inverse(view);



		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -10.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));



		//shader.uniform("u_Model", getEntity()->GetComponent<Tranform>()->GetModel());


		shader.use();

		//shader.attribute("a_Position", mesh);


		glBindTexture(GL_TEXTURE_2D, m_texture->m_texture->id());

		shader.uniform("u_View", view);
		shader.uniform("u_Model", getEntity()->getTransform()->getModelMatrix());
		shader.uniform("u_Projection", perspectiveProjection);

		glBindVertexArray(m_model->m_model->vao_id());


		// 3 = mesh data size
		glDrawArrays(GL_TRIANGLES, 0, m_model->m_model->vertex_count());

	}

}