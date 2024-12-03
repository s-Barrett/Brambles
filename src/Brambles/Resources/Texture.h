#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{
	struct TriangleRenderer;
	struct Texture : Resource
	{
		void onLoad();

	private:
		friend struct Brambles::TriangleRenderer;
		std::shared_ptr<rend::Texture> m_texture;
	};
}