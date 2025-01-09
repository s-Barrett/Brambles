#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Brambles
{
	struct Transform;
	struct Entity;

	struct Component
	{
		virtual void onInitialize() {}
		virtual void onTick() {}
		virtual void onRender() {}
	
	

		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Transform> getTransform();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		void setPosition(glm::vec3 position);
		void setRotation(glm::vec3 rotation);
		void setScale(glm::vec3 scale);

		void move(glm::vec3 move);
		void rotate(glm::vec3 rotate);
		void scale(glm::vec3 scale);

	private:
		friend struct Brambles::Entity;

		std::weak_ptr<Entity> m_entity;

		void tick();
		void render();
	};

}