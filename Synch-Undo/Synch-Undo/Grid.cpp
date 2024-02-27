#include "Grid.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <ctime>
#include <iostream>

#include "Cell.h"

Grid::Grid(GameObject* owner, const int windowWidth, const int windowHeight,
	const int cellSize)
	: Component(owner),
	windowWidth(windowWidth),
	windowHeight(windowHeight),
	rows(windowHeight / cellSize),
	cols(windowWidth / cellSize),
	cellSize(cellSize)
{
	cellObjects.resize(cols);

	for (int col = 0; col < cols; ++col) {
		cellObjects[col].resize(rows);
		for (int row = 0; row < rows; ++row) {
			const int posX = col * cellSize;
			const int posY = row * cellSize;

			GameObject* cellObject = new GameObject("cell");
			TransformComponent* transformComponent = new TransformComponent(cellObject, posX, posY, cellSize, cellSize);
			cellObject->AddComponent(transformComponent);
			Cell* newCell = new Cell(cellObject);
			cellObject->AddComponent(newCell);

			cellObjects[col][row] = cellObject;

			if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1) {
				newCell->SetCellState(Cell::Wall);
			}

			owner->AddChildGameObject(cellObject);
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

const Cell* Grid::GetCellAtPos(const int col, const int row) const
{
	if (col < 0 || col >= cols || row < 0 || row >= rows)
	{
		std::cout << "[Grid  -  GetCellAtPos] Try getting an invalid cell at pos! " << col << " | " << row << "\n";
		return nullptr;
	}

	const GameObject* cellObject = cellObjects[col][row];
	if (cellObject) {
		return cellObject->GetComponent<Cell>();
	}

	return nullptr;
}

bool Grid::IsCellEmpty(const int col, const int row) const {
	if (col < 0 || col >= cols || row < 0 || row >= rows)
	{
		std::cout << "[Grid  -  IsCellEmpty] Try checking is cell is empty at pos! " << col << " | " << row << "\n";
		return false;
	}

	const GameObject* cellObject = cellObjects[col][row];
	const Cell* cell = cellObject->GetComponent<Cell>();

	if (cell) {
		return cell->GetCellState() == Cell::Empty;
	}
	return false;
}

void Grid::SetCellState(const int col, const int row, const Cell::CellState newState) const
{
	if (col < 0 || col >= cols || row < 0 || row >= rows) {
		return;
	}

	const GameObject* cellObject = cellObjects[col][row];
	std::cout << "Set cell to wall at: " << col << "  |  " << row << "\n";
	Cell* cell = cellObject->GetComponent<Cell>();
	if (cell) {
		cell->SetCellState(newState);
	}
}

void Grid::CreateWallPatterns() const
{
	SetCellState(3, 1, Cell::Wall);
	SetCellState(3, 2, Cell::Wall);
	SetCellState(3, 3, Cell::Wall);
	SetCellState(3, 4, Cell::Wall);
	SetCellState(2, 4, Cell::Wall);

	SetCellState(7, 2, Cell::Wall);
	SetCellState(7, 3, Cell::Wall);
	SetCellState(7, 4, Cell::Wall);
	SetCellState(8, 2, Cell::Wall);

	SetCellState(4, 6, Cell::Wall);
	SetCellState(5, 6, Cell::Wall);
	SetCellState(5, 7, Cell::Wall);

	SetCellState(3, 9, Cell::Wall);
	SetCellState(3, 10, Cell::Wall);
	SetCellState(3, 11, Cell::Wall);
	SetCellState(4, 9, Cell::Wall);
	SetCellState(5, 9, Cell::Wall);
	SetCellState(6, 9, Cell::Wall);

	SetCellState(6, 13, Cell::Wall);
	SetCellState(7, 13, Cell::Wall);
	SetCellState(8, 10, Cell::Wall);
	SetCellState(9, 10, Cell::Wall);
	SetCellState(9, 11, Cell::Wall);
	SetCellState(9, 12, Cell::Wall);
	SetCellState(9, 13, Cell::Wall);
	SetCellState(8, 13, Cell::Wall);
	SetCellState(10, 10, Cell::Wall);
	SetCellState(11, 10, Cell::Wall);
	SetCellState(12, 10, Cell::Wall);

	SetCellState(11, 4, Cell::Wall);
	SetCellState(11, 5, Cell::Wall);
	SetCellState(11, 6, Cell::Wall);
	SetCellState(11, 7, Cell::Wall);
	SetCellState(12, 4, Cell::Wall);
	SetCellState(12, 5, Cell::Wall);
	SetCellState(13, 4, Cell::Wall);

	SetCellState(16, 2, Cell::Wall);
	SetCellState(17, 2, Cell::Wall);
	SetCellState(18, 1, Cell::Wall);
	SetCellState(18, 2, Cell::Wall);
	SetCellState(18, 3, Cell::Wall);

	SetCellState(16, 5, Cell::Wall);
	SetCellState(16, 6, Cell::Wall);
	SetCellState(16, 7, Cell::Wall);
	SetCellState(16, 8, Cell::Wall);
	SetCellState(17, 5, Cell::Wall);
	SetCellState(17, 6, Cell::Wall);
	SetCellState(17, 7, Cell::Wall);
	SetCellState(17, 8, Cell::Wall);
	SetCellState(17, 9, Cell::Wall);
	SetCellState(18, 5, Cell::Wall);
	SetCellState(18, 8, Cell::Wall);
	SetCellState(19, 5, Cell::Wall);

	SetCellState(20, 8, Cell::Wall);
	SetCellState(20, 9, Cell::Wall);
	SetCellState(21, 9, Cell::Wall);
	SetCellState(21, 10, Cell::Wall);

	SetCellState(14, 11, Cell::Wall);
	SetCellState(14, 12, Cell::Wall);
	SetCellState(15, 12, Cell::Wall);
	SetCellState(15, 13, Cell::Wall);
	SetCellState(16, 12, Cell::Wall);
	SetCellState(16, 13, Cell::Wall);
	SetCellState(17, 12, Cell::Wall);
	SetCellState(18, 11, Cell::Wall);
	SetCellState(18, 12, Cell::Wall);
	SetCellState(19, 11, Cell::Wall);
	SetCellState(19, 12, Cell::Wall);

	SetCellState(21, 3, Cell::Wall);
	SetCellState(21, 4, Cell::Wall);
	SetCellState(22, 3, Cell::Wall);
}
