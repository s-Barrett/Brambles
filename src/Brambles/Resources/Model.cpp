#include "Model.h"



namespace Brambles
{
	void Model::onLoad()//load the model
	{
		m_model = std::make_shared<rend::Model>(getPath());//Get the path of the model and returns to m_model

	}
}
