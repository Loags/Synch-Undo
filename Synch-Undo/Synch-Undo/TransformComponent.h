#pragma once
#include "Component.h"

class TransformComponent : public Component
{
public:
	TransformComponent(GameObject* owner, const int posX = 0.0f, const int posY = 0.0f, const int width = 0.0f, const int height = 0.0f);
	void Update() override;

	int GetX() const { return posX; }
	int GetY() const { return posY; }
	void SetPosition(int const x, int const y) { posX = x; posY = y; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	void SetSize(int const w, int const h) { width = w; height = h; }

private:
	int posX, posY;
	int width, height;
};

