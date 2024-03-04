#pragma once
#include <string>

class GameObject;


class Component {
private:
	std::string componentName;

public:
	explicit Component(std::string componentName, GameObject* owner);
	virtual ~Component() = default;
	virtual void Update() = 0;
	std::string GetComponentName() const { return componentName; }
	GameObject* GetOwner() const { return owner; }
	
protected:
	GameObject* owner;
};
