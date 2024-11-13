#include "Component.h"

namespace Brambles {

	void Component::onInitialize() {}
	void Component::onTick(){}
	void Component::onRender() {}


	void Component::tick() { onTick(); }
	void Component::render() { onRender(); }

}