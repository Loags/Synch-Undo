#include "GridComponent.h"

GridComponent::GridComponent(const std::shared_ptr<GameObject>& owner, int width, int height, int cellSize)
    : Component(owner), width(width), height(height), cellSize(cellSize) {}

void GridComponent::Update() {
    // Update logic for the grid, if any
}

void GridComponent::Render(SDL_Renderer* renderer) {
    // rendering code for the grid
}
