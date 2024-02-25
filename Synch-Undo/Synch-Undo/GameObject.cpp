#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::AddComponent(Component* component) {
	components.push_back(component);
}

void GameObject::AddChildGameObject(GameObject* child)
{
	children.push_back(child);
}

void GameObject::Render(SDL_Renderer* renderer) const
{
	for (const GameObject* child : children) {
		child->Render(renderer);
	}
	for (Component* component : components) {
		component->Render(renderer);
	}
}

void GameObject::Update() const
{
	for (const GameObject* child : children) {
		child->Update();
	}
	for (Component* component : components) {
		component->Update();
	}
}
