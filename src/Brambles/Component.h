#pragma once

#include <memory>

namespace Brambles
{

	struct Component
	{
		virtual void onInitialize();
		virtual void onTick();
		virtual void onRender();
	
		void tick();
		void render();
	};

}