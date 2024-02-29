#pragma once
#include <string>

class GameObject;


class Component {
public:
	explicit Component(GameObject* owner);
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual std::string GetName() const = 0;

protected:
	GameObject* owner;
};
