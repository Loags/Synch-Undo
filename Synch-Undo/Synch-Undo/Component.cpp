#include "Component.h"

Component::Component(std::string componentName, GameObject* owner) :
	componentName(std::move(componentName)),
	owner(owner)
{}
