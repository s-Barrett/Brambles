#include "Texture.h"


namespace Brambles
{

	void Texture::onLoad()
	{
		m_texture = std::make_shared<rend::Texture>(getPath());
	}

}
