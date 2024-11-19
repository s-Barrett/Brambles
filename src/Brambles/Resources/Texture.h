#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{

	struct Texture : Resource
	{
		void onLoad();

	private:
		std::shared_ptr<rend::Texture> m_texture;
	};
}