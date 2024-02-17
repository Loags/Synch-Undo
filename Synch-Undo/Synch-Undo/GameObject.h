#pragma once
#include <string>
#include <vector>
#include <memory>
#include <SDL_render.h>

class Component;

class GameObject {
public:
	explicit GameObject(std::string name);
	void AddComponent(std::shared_ptr<Component> component);
	template <typename T> T* GetComponent();
	void Render(SDL_Renderer* renderer);
	void Update();

private:
	std::string name;
	std::vector<std::shared_ptr<Component>> components;
};
