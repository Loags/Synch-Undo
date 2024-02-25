#pragma once
#include <SDL.h>

class GameObject;


class Component {
public:
	explicit Component(GameObject* owner);
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

protected:
	GameObject* owner;
};
