#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

namespace Brambles
{
	struct Model : Resource
	{
		void onLoad();
	private:
		std::shared_ptr<rend::Model> m_model;

	};
}