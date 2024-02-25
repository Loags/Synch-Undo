#pragma once
#include <SDL.h>
#include <string>

class GameObject;


class Component {
public:
	explicit Component(GameObject* owner);
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual std::string GetName() const = 0;

protected:
	GameObject* owner;
};
