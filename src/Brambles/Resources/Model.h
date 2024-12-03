#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{
	struct TriangleRenderer;
	struct Model : Resource
	{
		void onLoad();

	private:
		friend struct Brambles::TriangleRenderer;
		std::shared_ptr<rend::Model> m_model;

	};
}