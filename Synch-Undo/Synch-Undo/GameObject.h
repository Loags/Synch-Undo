#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL_render.h>

class Component;

class GameObject {
public:
	explicit GameObject(GameObject* owner, std::string name);
	void PrintComponentsAndChildren(const int level = 0) const;
	void AddComponent(Component* component);
	void AddChildGameObject(GameObject* child);
	void Render(SDL_Renderer* renderer) const;
	void Update() const;
	void Destroy();
	int GetChildrenCount() const { return children.size(); }
	GameObject* GetParentObject() const { return owner; }

	template<typename T>
	T* GetComponentInChildren() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		// First, check direct children
		for (GameObject* child : children) {
			T* component = child->GetComponent<T>();
			if (component) {
				return component;
			}
		}

		// If not found, recursively check each child's children
		for (GameObject* child : children) {
			T* componentInChildren = child->GetComponentInChildren<T>();
			if (componentInChildren) {
				return componentInChildren;
			}
		}

		// If we get here, no component of type T was found in this GameObject's children
		return nullptr;
	}

	template<typename T>
	GameObject* GetGameObjectWithComponent() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		// Check direct children
		std::cout << "Child count: " << children.size() << "\n";
		for (GameObject* child : children) {
			std::cout << "Check: " << child->name << "\n";
			const T* component = child->GetComponent<T>();
			if (component) {
				std::cout << "Found child!\n";
				return child; // Return the GameObject that has the component
			}
		}

		// Recursively check each child's children
		for (GameObject* child : children) {
			GameObject* gameObjectWithComponent = child->GetGameObjectWithComponent<T>();
			if (gameObjectWithComponent) {
				std::cout << "Found child!\n";

				return gameObjectWithComponent;
			}
		}

		// If not found, return nullptr
		std::cout << "No GameObject found with the specific component\n";
		return nullptr;
	}

	template <typename T>
	T* GetComponent() const
	{
		for (Component* component : components) {
			T* casted = dynamic_cast<T*>(component);
			if (casted) {
				return casted;
			}
		}
		return nullptr;
	}

private:
	GameObject* owner;
	std::vector<GameObject*> children;
	std::string name;
	std::vector<Component*> components;
};