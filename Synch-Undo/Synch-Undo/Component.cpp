#include "Component.h"
#include "GameObject.h"

Component::Component(std::shared_ptr<GameObject> owner) :
	owner(std::move(owner))
{}
