#include "Component.h"
#include "Entity.h"

namespace Brambles {


	void Component::onInitialize() {}
	void Component::onTick() {}
	void Component::onRender() {}

	void Component::tick() 
	{
		onTick();
	}
	void Component::render()
	{ 
		onRender(); 
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return m_entity;
	}

}