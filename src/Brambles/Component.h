#include <memory>

namespace Brambles
{

	struct Component
	{
		virtual void on_initialize();
		virtual void on_tick();

		void tick();
	};

}