#include <GL/glew.h>

namespace rend
{
	struct TriangleRenderer
	{
	public:

		TriangleRenderer();
		~TriangleRenderer();

		void onInit();



		
	private:

		void onDisplay();

		GLuint programId;
		GLuint vboId;
		GLuint vaoId;

	};

}