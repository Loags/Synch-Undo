#pragma once
#include "Component.h"
#include <SDL.h>

class GameObject;

class GridComponent : public Component {
public:
    int width, height; // Dimensions of the grid
    int cellSize;      // Size of each cell in the grid

    GridComponent(const std::shared_ptr<GameObject>& owner, int width, int height, int cellSize);
    void Update() override;
    void Render(SDL_Renderer* renderer);
};
