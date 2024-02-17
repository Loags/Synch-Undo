#include "Component.h"
#include "GameObject.h"

Component::Component(const std::shared_ptr<GameObject> owner) :
	owner(std::move(owner))
{}
