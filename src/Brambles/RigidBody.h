#include "Component.h"


namespace Brambles
{
	struct RigidBody : public Component
	{
		void onTick();

		void renderDebug();

		void setMass(float _mass) { m_mass = _mass; }

		float getMass() { return m_mass; }


	private:
		float m_mass{ 1.0f };
	};



}
