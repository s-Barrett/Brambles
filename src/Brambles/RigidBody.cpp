#include "RigidBody.h"
#include "Transform.h"
#include "DebugRenderer.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "Core.h"

#include <vector>
#include <iostream>

namespace Brambles
{

    void RigidBody::onTick()
    {
		std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getEntity()->getCore()->seekComponents(boxColliders);

		for (auto boxCollider : boxColliders)
		{
			if (boxCollider->getTransform() == getTransform())
				continue;
			
			if (boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
			{
				float amount = 0.001f;
				float step = 0.001f;
				while (true)
				{
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() + glm::vec3(amount, 0, 0));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() - glm::vec3(amount, 0, 0));
					setPosition(getPosition() - glm::vec3(amount, 0, 0));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() + glm::vec3(amount, 0, 0));
					setPosition(getPosition() + glm::vec3(0, 0, amount));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() - glm::vec3(0, 0, amount));
					setPosition(getPosition() - glm::vec3(0, 0, amount));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() + glm::vec3(0, 0, amount));
					setPosition(getPosition() + glm::vec3(0, amount, 0));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() - glm::vec3(0, amount, 0));
					setPosition(getPosition() - glm::vec3(0, amount, 0));
					if (!boxCollider->isColliding(getEntity()->getComponent<BoxCollider>()))
						break;

					setPosition(getPosition() + glm::vec3(0, amount, 0));
					amount += step;
				}

			}
		}
	}
}
