#include "GameObject.h"
#include <iostream>
#include "Component.h"
#include "RenderComponent.h"

class TransformComponent;

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::PrintComponentsAndChildren(const int level) const
{
	const std::string indent(level * 6, ' ');

	std::cout << indent << "GameObject: " << name << "\n";

	if (!components.empty()) {
		std::cout << indent << "  Components:\n";
		for (const Component* comp : components) {
			std::cout << indent << "    - " << comp->GetName() << "\n";
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
	for (const GameObject* child : children) {

		if (child)
			child->Render(renderer);

		const RenderComponent* renderComp = child->GetComponent<RenderComponent>();

		if (!renderComp) continue;

		const TransformComponent* transform = child->GetComponent<TransformComponent>();
		if (transform) {
			renderComp->Render(renderer, transform, renderComp->GetRenderColor());
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
