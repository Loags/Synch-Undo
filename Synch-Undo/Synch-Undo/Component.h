#pragma once
#include <memory>
#include <SDL.h>

class GameObject;

class Component {
public:
	explicit Component(const std::shared_ptr<GameObject> owner);
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

protected:
	std::weak_ptr<GameObject> owner;
};
