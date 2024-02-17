#pragma once
#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject {
public:
    explicit GameObject(std::string name);
    void AddComponent(std::shared_ptr<Component> component);
    template <typename T> T* GetComponent();

private:
    std::string name;
    std::vector<std::shared_ptr<Component>> components;
};
