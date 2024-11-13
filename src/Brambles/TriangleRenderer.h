#include <GL/glew.h>
#include "Component.h"
#include <rend/rend.h>

namespace Brambles
{
	struct TriangleRenderer : Component
	{
		TriangleRenderer();



	public:

		
		
	private:

		void TriangleRenderer::onRender();

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;
		rend::Mesh mesh;
		rend::Shader shader;


	};

}