#include "Texture.h"



namespace Brambles
{
	void Texture::onLoad()
	{
		m_texture = std::make_shared<rend::Texture>(getPath()); //Get the path of the texture and returns to m_texture
	}
}
