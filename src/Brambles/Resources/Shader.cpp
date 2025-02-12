#include "Shader.h"


namespace Brambles
{
	void Shader::onLoad()
	{
		m_shader = std::make_shared<rend::Shader>(getPath(), getPath()); //Get the path of the texture and returns to m_texture
	}

}