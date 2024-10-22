#pragma once
#include <GL/glew.h>

struct RenderTexture
{
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void bind();
	void unbind();
	GLuint getTexture();

private:
	GLuint m_fboId;
	GLuint m_texId;
	GLuint m_rboId;
};