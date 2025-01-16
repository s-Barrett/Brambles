#include "Resource.h"


namespace Brambles
{
	std::string Resource::getPath() const
	{
		return m_path;
	}

	void Resource::load()//loading the resource
	{
		onLoad();
	}
}