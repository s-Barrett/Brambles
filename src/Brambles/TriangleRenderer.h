#include <GL/glew.h>
#include "Component.h"
#include <rend/rend.h>

namespace Brambles
{
	struct Model;
	struct Texture;
	struct TriangleRenderer : Component
	{
		TriangleRenderer();



	public:

		void setTexture(std::shared_ptr<Texture> _texture);
		void setModel(std::string _modelPath);
  


		
	private:

		void TriangleRenderer::onRender();
		

		

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;
		rend::Mesh mesh;
		rend::Shader shader;
		GLuint texture;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Model> m_model;


	};

}