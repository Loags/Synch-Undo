#pragma once
#include <string>
#include <vector>
#include <SDL_render.h>

class Component;

class GameObject {
public:
	explicit GameObject(std::string name);
	void PrintComponentsAndChildren(const int level = 0) const;
	void AddComponent(Component* component);
	void AddChildGameObject(GameObject* child);
	void Render(SDL_Renderer* renderer) const;
	void Update() const;
	void Destroy();

	template <typename T>
	T* GetComponent() const {
		for (Component* component : components) {
			T* casted = dynamic_cast<T*>(component);
			if (casted) {
				return casted;
			}
		}
		return nullptr;
	}

private:
	std::string name;
	std::vector<Component*> components;
	std::vector<GameObject*> children;
};
