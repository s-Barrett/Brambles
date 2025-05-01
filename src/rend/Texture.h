#include <GL/glew.h>

#include <vector>
#include <string>
namespace rend
{

	struct Texture
	{
		Texture(const std::string& _path);
		GLuint id();

		

	private:
		GLuint m_id;


		int m_width = 0;
		int m_hight = 0;
		bool m_dirty = true;

		std::vector<unsigned char> m_data;

	};
}