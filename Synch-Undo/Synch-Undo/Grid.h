#pragma once
#include "Component.h"
#include <vector>
#include "Cell.h"

class GameObject;

class Grid : public Component {

private:
	int windowWidth;
	int windowHeight;
	int rows;
	int cols;
	int cellSize;
	std::vector<std::vector<GameObject*>> cellObjects;

public:
	Grid(GameObject* owner, const int windowWidth, const int windowHeight, const int cellSize);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	std::string GetName() const override { return "Grid"; }

	int GetCellSize() const { return cellSize; }
	const Cell* GetCellAtPos(const int col, const int row) const;
	bool IsCellEmpty(const int col, const int row) const;

	void SetCellState(const int col, const int row, const Cell::CellState newState) const;
	void CreateWallPatterns() const;
};
