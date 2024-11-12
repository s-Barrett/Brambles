#include "TriangleRenderer.h"

namespace rend
{


	void TriangleRenderer::onInit()
	{
		programId = glCreateProgram();

		glGenBuffers(1, &vboId);
		glGenVertexArrays(1, &vaoId);

		glBindVertexArray(vaoId);

		GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,  // Bottom left
		 0.5f, -0.5f, 0.0f,  // Bottom right
		 0.0f,  0.5f, 0.0f   // Top
		};

		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void TriangleRenderer::onDisplay()
	{
		glUseProgram(programId);
		glBindVertexArray(vaoId);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

}