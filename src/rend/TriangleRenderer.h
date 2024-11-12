#include <GL/glew.h>

namespace rend
{
	struct TriangleRenderer
	{
	public:

		void TriangleRenderer::onInit();



		
	private:

		void TriangleRenderer::onDisplay();

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;

	};

}