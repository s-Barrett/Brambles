#include "TriangleRenderer.h"
#include "glm/glm.hpp"


namespace Brambles
{




	TriangleRenderer::TriangleRenderer()
		: shader("../assets/shaders/vertexShader.glsl", "../assets/shaders/fragmentShader.glsl")
	{
	
		mesh;
		rend::Face a;

		a.a.position = glm::vec3(0, 1, 0);
		a.b.position = glm::vec3(-1, -1, 0);
		a.c.position = glm::vec3(1, -1, 0);

		mesh.addFace(a);


	}

	void TriangleRenderer::setTexture(std::shared_ptr<rend::Texture> _texture)
	{
		m_texture = _texture;
	}




	void TriangleRenderer::onRender()
	{


		glm::mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), (float)700 / (float)700, 0.1f, 500.f);

		//prepare view matrix
		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0, 0, 0.0f));
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


		glBindTexture(GL_TEXTURE_2D, m_texture->id());

		shader.uniform("u_View", view);
		shader.uniform("u_Model", model);
		shader.uniform("u_Projection", perspectiveProjection);

		glBindVertexArray(mesh.getVAOId());

		// 3 = mesh data size
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

}