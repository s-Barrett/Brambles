#include "Model.h"



namespace Brambles
{
	void Model::onLoad()
	{
		m_model = std::make_shared<rend::Model>(getPath());

	}
}
