#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>
#include <stdexcept>

namespace Brambles 
{

	std::shared_ptr<Entity> Component::getEntity()
	{
		auto entity = m_entity.lock();
		if (!entity) {
			std::cerr << "Entity is null in getEntity()" << std::endl;
			// Handle the error here to avoid exceptions later
			throw std::runtime_error("Entity is null in getEntity()");
		}
		return entity;
	}

	std::shared_ptr<Transform> Component::getTransform()
	{
		auto entity = getEntity();
		if (!entity) {
			throw std::runtime_error("Entity is null in getTransform()");
		}
		auto transform = entity->getComponent<Transform>();
		if (!transform) {
			throw std::runtime_error("Transform component is missing in getTransform()");
		}
		return transform;
	}

	std::shared_ptr<Gui> Component::getGui()
	{
		auto entity = getEntity();
		if (!entity) {
			throw std::runtime_error("Entity is null in getGui()");
		}
		auto gui = entity->getCore()->getGui();
		if (!gui) {
			throw std::runtime_error("Gui is missing in getGui()");
		}
		return gui;
	}

	glm::vec3 Component::getPosition()
	{
		return getTransform()->getPosition();
	}

	void Component::setPosition(glm::vec3 _position)
	{
		getTransform()->setPosition(_position);
	}

	glm::vec3 Component::getRotation()
	{
		return getTransform()->getRotation();
	}

	void Component::setRotation(glm::vec3 rotation)
	{
		getTransform()->setRotation(rotation);
	}

	glm::vec3 Component::getScale()
	{
		return getTransform()->getScale();
	}

	void Component::setScale(glm::vec3 scale)
	{
		getTransform()->setScale(scale);
	}

	void Component::move(glm::vec3 move)
	{
		getTransform()->move(move);
	}

	void Component::rotate(glm::vec3 rotate)
	{
		getTransform()->rotate(rotate);
	}

	void Component::scale(glm::vec3 scale)
	{
		getTransform()->scale(scale);  
	}


	void Component::gui()
	{
		auto entity = m_entity.lock();
		assert(entity && "Entity is null in gui()");
		if (!entity) {
			std::cerr << "Entity is null in gui()" << std::endl;
			return;
		}
		onGui();
	}

	void Component::tick()
	{
		auto entity = m_entity.lock();
		assert(entity && "Entity is null in tick()");
		if (!entity) {
			std::cerr << "Entity is null in tick()" << std::endl;
			return;
		}
		onTick();
	}

	void Component::render()
	{
		auto entity = m_entity.lock();
		assert(entity && "Entity is null in render()");
		if (!entity) {
			std::cerr << "Entity is null in render()" << std::endl;
			return;
		}
		onRender();
	}

}

