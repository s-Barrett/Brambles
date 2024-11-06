#include "Texture.h"
#include<exception>
#include <stb_image.h>


namespace rend
{

	Texture::Texture(const std::string& _path)
		:m_id(0)
		, m_hight(0)
		, m_width(0)
		, m_dirty(false)

	{
		unsigned char* data = stbi_load(_path.c_str(), &m_width, &m_hight, NULL, 4);

		if (!data)
		{
			throw std::exception();
		}

		for (size_t i = 0; i < m_width * m_hight * 4; ++i)
		{
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

		if (m_dirty) {

			glBindTexture(GL_TEXTURE_2D, m_id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_data.at(0));

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			m_dirty = false;



		}
		return m_id;
	}
}