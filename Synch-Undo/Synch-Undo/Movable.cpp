#include "Movable.h"
#include "Grid.h"
#include "TransformComponent.h"

Movable::Movable(const GameObject* movableOwner, const int offSet)
	: movableOwner(movableOwner),
	offSet(offSet)
{
}

void Movable::Move(const GameObject* gridObject, const int deltaX, const int deltaY) const
{
	const Grid* grid = gridObject->GetComponent<Grid>();
	TransformComponent* transform = movableOwner->GetComponent<TransformComponent>();

	const int newPosX = transform->GetX() + deltaX;
	const int newPosY = transform->GetY() + deltaY;

	const int cellSize = grid->GetCellSize();
	const int gridX = (newPosX + offSet) / cellSize;
	const int gridY = (newPosY + offSet) / cellSize;

	Cell* currentCell = grid->GetCellAtPos(transform->GetX() / cellSize, transform->GetY() / cellSize);
	Cell* targetCell = grid->GetCellAtPos(gridX, gridY);

	if (targetCell == nullptr) return;

	if (targetCell->GetCellState() == Cell::Empty) {
		currentCell->SetCellState(Cell::Empty);
		targetCell->SetCellState(Cell::Occupied);
		transform->SetPosition(newPosX, newPosY);
	}
}
