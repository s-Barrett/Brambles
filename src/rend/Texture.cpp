#include "Texture.h"
#include <exception>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace rend {

	Texture::Texture(const std::string& _path)
		: m_id(0), m_hight(0), m_width(0), m_dirty(false) {

		unsigned char* data = stbi_load(_path.c_str(), &m_width, &m_hight, NULL, 4);

		if (!data) {
			throw std::exception();
		}

		for (size_t i = 0; i < m_width * m_hight * 4; ++i) {
			m_data.push_back(data[i]);
		}
		m_dirty = true;

		free(data);
	}

	GLuint Texture::id()
	{
		if (!m_id)
		{
			glGenTextures(1, &m_id);
			if (!m_id)
			{
				throw std::exception();
			}
		}

		if (m_dirty)
		{
			glBindTexture(GL_TEXTURE_2D, m_id);

			// Determine if the texture is power-of-two
			bool isPowerOfTwo = (m_width & (m_width - 1)) == 0 && (m_hight & (m_hight - 1)) == 0;

			// Required for NPOT textures in WebGL
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			if (isPowerOfTwo)
			{
				// POT textures can use mipmaps
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				// NPOT textures cannot use mipmaps
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

			// Upload the texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_data.at(0));

			if (isPowerOfTwo)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			glBindTexture(GL_TEXTURE_2D, 0);
			m_dirty = false;
		}

		return m_id;
	}


}
