#include <GL/glew.h>
#include "Component.h"
#include <rend/rend.h>

namespace Brambles
{
	struct TriangleRenderer : Component
	{
		TriangleRenderer();



	public:

		void setTexture(std::shared_ptr<rend::Texture> _texture);
  


		
	private:

		void TriangleRenderer::onRender();
		

		

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;
		rend::Mesh mesh;
		rend::Shader shader;
		GLuint texture;
		std::shared_ptr<rend::Texture> m_texture;


	};

}