#include <GL/glew.h>

#include <vector>
#include <string>


struct Texture
{
	Texture(const std::string& _path);
	GLuint id();

private:
	GLuint m_id;


	int m_width;
	int m_hight;
	bool m_dirty;

	std::vector<unsigned char> m_data;

};