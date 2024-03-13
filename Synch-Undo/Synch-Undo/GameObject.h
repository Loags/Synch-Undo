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
	void Reparent(GameObject* newParent);
	int GetChildrenCount() const { return children.size(); }
	GameObject* GetParentObject() const { return owner; }
	GameObject* GetRootObject();
	std::string GetName() const { return name; }

	template<typename T>
	T* GetComponentInChildren() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (GameObject* child : children) {
			T* component = child->GetComponent<T>();
			if (component) {
				return component;
			}
		}

		for (GameObject* child : children) {
			T* componentInChildren = child->GetComponentInChildren<T>();
			if (componentInChildren) {
				return componentInChildren;
			}
		}

		return nullptr;
	}

	template<typename T>
	GameObject* GetGameObjectWithComponent() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		for (GameObject* child : children) {
			const T* component = child->GetComponent<T>();
			if (component) {
				return child;
			}
		}

		for (GameObject* child : children) {
			GameObject* gameObjectWithComponent = child->GetGameObjectWithComponent<T>();
			if (gameObjectWithComponent) {
				std::cout << "Found child!\n";

				return gameObjectWithComponent;
			}
		}

		return nullptr;
	}

	template<typename T>
	std::vector<GameObject*> GetAllGameObjectWithComponent() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");
		std::vector<GameObject*> gameObjectsWithComponent;

		if (GetComponent<T>() != nullptr) {
			gameObjectsWithComponent.push_back(const_cast<GameObject*>(this));
		}

		for (const GameObject* child : children) {
			auto childGameObjects = child->GetAllGameObjectWithComponent<T>();
			gameObjectsWithComponent.insert(gameObjectsWithComponent.end(), childGameObjects.begin(), childGameObjects.end());
		}

		return gameObjectsWithComponent;
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