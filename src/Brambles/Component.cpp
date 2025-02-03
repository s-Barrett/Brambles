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

		// Retrieve the Transform component from the entity
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

		// Retrieve the GUI instance from the core system
		auto gui = entity->getCore()->getGui();
		if (!gui) {
			throw std::runtime_error("Gui is missing in getGui()");
		}
		return gui;
	}

	// Position functions
	glm::vec3 Component::getPosition()
	{
		return getTransform()->getPosition();
	}


	// Rotation functions
	glm::vec3 Component::getRotation()
	{
		return getTransform()->getRotation();
	}


	// Scale functions
	glm::vec3 Component::getScale()
	{
		return getTransform()->getScale();
	}



	// Transformation operations
	void Component::setMove(glm::vec3 move)
	{
		getTransform()->move(move);
	}

	void Component::setRotate(glm::vec3 rotate)
	{
		getTransform()->rotate(rotate);
	}

	void Component::setScale(glm::vec3 scale)
	{
		getTransform()->scale(scale);
	}

	// GUI rendering function
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

	// Per-frame update function
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

	// Rendering function
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
