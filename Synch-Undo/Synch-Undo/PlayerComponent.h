#pragma once
#include "Component.h"
#include <SDL.h>

class GameObject;

class PlayerComponent : public Component {
public:
	int x, y;

	PlayerComponent(GameObject* owner, const int x, const int y);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
};
