#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{
	struct Renderer;
	struct Texture : Resource
	{
		void onLoad();

	private:
		friend struct Brambles::Renderer;
		std::shared_ptr<rend::Texture> m_texture;
	};
}