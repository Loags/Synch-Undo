#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::AddComponent(std::shared_ptr<Component> component) {
	components.push_back(component);
}

void GameObject::Render(SDL_Renderer* renderer) const
{
	for (const std::shared_ptr<Component>& component : components) {
		component->Render(renderer);
	}
}

void GameObject::Update() const
{
	for (const std::shared_ptr<Component>& component : components) {
		component->Update();
	}
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
