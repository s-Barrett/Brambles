#include "BoxCollider.h"
#include "Transform.h"
#include "Entity.h"
#include "DebugRenderer.h"
#include "Core.h"


namespace Brambles
{
	bool BoxCollider::isColliding(std::shared_ptr<BoxCollider> _other)
	{

		glm::vec3 a = getTransform()->getPosition() + m_offset;
		glm::vec3 b = _other->getTransform()->getPosition() + _other->m_offset;

		glm::vec3 sizeA = m_size / 2.0f; 
		glm::vec3 sizeB = _other->m_size / 2.0f;

		if (a.x + sizeA.x < b.x - sizeB.x || a.x - sizeA.x > b.x + sizeB.x)
		{
			return false;
		}
		if (a.y + sizeA.y < b.y - sizeB.y || a.y - sizeA.y > b.y + sizeB.y)
		{
			return false;
		}
		if (a.z + sizeA.z < b.z - sizeB.z || a.z - sizeA.z > b.z + sizeB.z)
		{
			return false;
		}

		return true;


	}

}