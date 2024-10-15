#include "Component.h"

namespace Brambles {

	void Component::on_initialize() {}
	void Component::on_tick(){}


	void Component::tick() { on_tick(); }

}