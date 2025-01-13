#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"



namespace Brambles
{
	void RigidBody::onTick()
	{
		glm::vec3 pos = getTransform()->getPosition();
		pos.y -= 0.01f;
		getTransform()->setPosition(pos);
		std::vector<std::shared_ptr<BoxCollider>> colliders;
		getEntity()->getCore()->seekComponents(colliders);
		for (auto& c : colliders)
		{
			if (c->colliding(*getEntity()->getComponent<BoxCollider>()))
			{
				pos.y += 0.01f;
				getTransform()->setPosition(pos);
				break;
			}
		}
	}
}