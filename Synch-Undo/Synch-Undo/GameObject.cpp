#include "GameObject.h"
#include <iostream>
#include "Component.h"

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::PrintComponentsAndChildren(const int level) const
{
	// spaces per hierarchy level
	const std::string indent(level * 6, ' ');

	// Print the GameObject name with indent
	std::cout << indent << "GameObject: " << name << "\n";

	// Print components if any
	if (!components.empty()) {
		std::cout << indent << "  Components:\n";
		for (const Component* comp : components) {
			std::cout << indent << "    - " << comp->GetName() << "\n";
		}
	}

	// Print children if any
	if (!children.empty()) {
		std::cout << indent << "  Children:\n";
		for (const GameObject* child : children) {
			child->PrintComponentsAndChildren(level + 1);
		}
	}
}

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
