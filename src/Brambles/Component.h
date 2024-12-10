#pragma once

#include <memory>

namespace Brambles
{
	struct Entity;
	struct Component
	{
		virtual void onInitialize();
		virtual void onTick();
		virtual void onRender();
	
		void tick();
		void render();

		std::shared_ptr<Entity> getEntity();


	private:

		friend struct Entity;
		std::shared_ptr<Entity> m_entity;
		

	};

}