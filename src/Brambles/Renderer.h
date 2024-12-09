#include <GL/glew.h>
#include "Component.h"
#include <rend/rend.h>

namespace Brambles
{
	struct Model;
	struct Texture;
	struct Renderer : Component
	{
		Renderer();



	public:

		void setTexture(std::shared_ptr<Texture> _texture);
		void setModel(std::shared_ptr<Model> _modelPath);




	private:

		void Renderer::onRender();

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;
		GLuint texture;

		rend::Mesh mesh;
		rend::Shader shader;

		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Model> m_model;


	};

}