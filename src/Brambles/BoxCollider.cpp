#include "BoxCollider.h"
#include "Transform.h"
#include "Entity.h"
#include "DebugRenderer.h"
#include "Core.h"


namespace Brambles
{

	void BoxCollider::renderDebug()
	{
		if (debugRenderer == true)
		{
			if (!getEntity()->hasComponent<DebugRenderer>())
			{
				getEntity()->addComponent<DebugRenderer>();
			}

			auto collider = getEntity()->getComponent<BoxCollider>();
			if (collider)
			{
				getEntity()->getComponent<DebugRenderer>()->drawBoxCollider(collider, glm::vec3(1.0f, 0.0f, 0.0f));
			}

		}
		else
		{

		}
	
	}

	void BoxCollider::onRender()
	{
		renderDebug();
		
	}

	bool BoxCollider::isColliding(std::shared_ptr<BoxCollider> _other)
	{
		glm::vec3 a = getTransform()->getPosition() + m_offset;
		glm::vec3 b = _other->getTransform()->getPosition() + _other->m_offset;

		glm::vec3 ahs = m_size / 2.0f;
		glm::vec3 bhs = _other->m_size / 2.0f;

		std::cout << "Entity 1 Position: " << a.x << ", " << a.y << ", " << a.z << std::endl;
		std::cout << "Entity 2 Position: " << b.x << ", " << b.y << ", " << b.z << std::endl;




		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}

		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}

		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}


		return true;
	}

}
