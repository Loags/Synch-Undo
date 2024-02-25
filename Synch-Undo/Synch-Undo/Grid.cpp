#include "Grid.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <ctime>

Grid::Grid(GameObject* owner, const int windowWidth, const int windowHeight,
	const int cellSize)
	: Component(owner),
	windowWidth(windowWidth),
	windowHeight(windowHeight),
	rows(windowHeight / cellSize),
	cols(windowWidth / cellSize),
	cellSize(cellSize)
{
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			int posX = col * cellSize;
			int posY = row * cellSize;

			GameObject* cellObject = new GameObject("cell");
			TransformComponent* transformComponent = new TransformComponent(cellObject, posX, posY, cellSize, cellSize);
			cellObject->AddComponent(transformComponent);
			Cell* newCell = new Cell(cellObject);
			cellObject->AddComponent(newCell);

			if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1) {
				newCell->SetCellState(Cell::Wall);
			}

			owner->AddChildGameObject(cellObject);
			cellObjects.push_back(cellObject);
		}
	}
	CreateWallPatterns();
}


void Grid::Update() {
	// Update logic for the grid, if any
}

void Grid::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Draw horizontal and vertical lines
	for (int row = 0; row <= rows; ++row) {
		SDL_RenderDrawLine(renderer, 0, row * cellSize, cols * cellSize, row * cellSize);
	}
	for (int col = 0; col <= cols; ++col) {
		SDL_RenderDrawLine(renderer, col * cellSize, 0, col * cellSize, rows * cellSize);
	}
}

void Grid::SetCellState(const int row, const int col, const Cell::CellState newState) const
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		return;
	}

	const GameObject* cellObject = cellObjects[row * cols + col];
	Cell* cell = cellObject->GetComponent<Cell>();
	if (cell) {
		cell->SetCellState(newState);
	}
}

void Grid::CreateWallPatterns() const
{
	// Seed random number generator
	std::srand(std::time(nullptr));

	int wallsToPlace = 21;
	while (wallsToPlace > 0) {
		const int row = std::rand() % (rows - 2) + 2;
		const int col = std::rand() % (cols - 2) + 2;

		// Simple pattern: place one Wall cell and two adjacent ones
		SetCellState(row, col, Cell::Wall);
		if (std::rand() % 2) { 
			SetCellState(row, (col + 1) % (cols - 1), Cell::Wall);
			SetCellState(row, (col + 2) % (cols - 1), Cell::Wall);
		}
		else {
			SetCellState((row + 1) % (rows - 1), col, Cell::Wall);
			SetCellState((row + 2) % (rows - 1), col, Cell::Wall);
		}

		wallsToPlace -= 3;
	}
}
