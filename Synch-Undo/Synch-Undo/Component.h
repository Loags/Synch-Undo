#pragma once
#include <memory>

class GameObject;

class Component {
public:
    explicit Component(std::shared_ptr<GameObject> owner);
    virtual ~Component() = default;
    virtual void update() = 0;

protected:
    std::weak_ptr<GameObject> owner;
};
