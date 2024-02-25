#pragma once
#include "Component.h"
#include <vector>

#include "Cell.h"


class GameObject;

class Grid : public Component {
public:
	int windowWidth, windowHeight, rows, cols;
	int cellSize;
	std::vector<GameObject*> cellObjects;

	Grid(GameObject* owner, const int windowWidth, const int windowHeight, const int cellSize);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	std::string GetName() const override { return "Grid"; }

	void SetCellState(const int row, const int col, const Cell::CellState newState) const;
	void CreateWallPatterns() const;
};
