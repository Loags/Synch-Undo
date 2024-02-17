#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

template <typename T>
T* GameObject::GetComponent() {
    for (auto& comp : components) {
        T* casted = dynamic_cast<T*>(comp.get());
        if (casted) {
            return casted;
        }
    }
    return nullptr;
}
