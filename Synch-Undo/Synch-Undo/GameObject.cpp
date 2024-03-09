#include "GameObject.h"
#include <iostream>
#include "Component.h"
#include "RenderComponent.h"


class TransformComponent;

GameObject::GameObject(GameObject* owner, std::string name) :
	owner(owner),
	name(std::move(name))
{}

void GameObject::PrintComponentsAndChildren(const int level) const
{
	const std::string indent(level * 6, ' ');

	std::cout << indent << "GameObject: " << name << "\n";

	if (!components.empty()) {
		std::cout << indent << "  Components:\n";
		for (const Component* comp : components) {
			std::cout << indent << "    - " << comp->GetComponentName() << "\n";
		}
	}

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
	// Render this object's components first, if any
	for (const auto& component : components) {
		const RenderComponent* renderComp = dynamic_cast<const RenderComponent*>(component);
		if (renderComp) {
			const TransformComponent* transform = GetComponent<TransformComponent>();
			if (transform) {
				renderComp->Render(renderer, transform, renderComp->GetRenderColor());
			}
		}
	}

	// Then recursively render all children
	for (const GameObject* child : children) {
		if (child) {
			child->Render(renderer);
		}
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

void GameObject::Reparent(GameObject* newParent) {
	// Remove from current parent
	if (this->owner) {
		auto& siblings = this->owner->children;
		siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
	}

	// Set new parent
	this->owner = newParent;

	// Add to new parent's children list
	if (newParent) {
		newParent->children.push_back(this);
	}
}


GameObject* GameObject::GetRootObject()
{
	GameObject* current = this;
	while (current != nullptr && current->owner != nullptr) {
		current = current->owner;
	}
	return current;
}
