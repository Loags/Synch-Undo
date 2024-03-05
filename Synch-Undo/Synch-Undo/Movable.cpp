#include "Movable.h"
#include "Grid.h"
#include "TransformComponent.h"

Movable::Movable(const GameObject* movableOwner, const int offSet) :
	offSet(offSet),
	movableOwner(movableOwner),
	facingDirection(Direction::South)
{
}

bool Movable::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	const Grid* grid = gridObject->GetComponent<Grid>();
	const int cellSize = grid->GetCellSize();

	TransformComponent* transform = movableOwner->GetComponent<TransformComponent>();

	int newPosX = transform->GetX();
	int newPosY = transform->GetY();

	switch (newFacingDirection) {
	case Direction::North:
		newPosY = transform->GetY() - cellSize;
		break;
	case Direction::South:
		newPosY = transform->GetY() + cellSize;
		break;
	case Direction::East:
		newPosX = transform->GetX() + cellSize;
		break;
	case Direction::West:
		newPosX = transform->GetX() - cellSize;
		break;
	}

	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transform->GetX(), transform->GetY());
	const std::pair<int, int> gridPosTarget = grid->GetPositionToGridCoords(newPosX + offSet, newPosY + offSet);

	Cell* currentCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
	Cell* targetCell = grid->GetCellAtPos(gridPosTarget.first, gridPosTarget.second);

	if (targetCell == nullptr) return false;

	if (targetCell->GetCellState() == Cell::Empty) {
		currentCell->SetCellState(Cell::Empty);
		currentCell->SetCharacterObjectRef(nullptr);

		targetCell->SetCellState(Cell::Occupied);
		targetCell->SetCharacterObjectRef(movableOwner);

		transform->SetPosition(newPosX, newPosY);
		SetFacingDirection(newFacingDirection);
		return true;
	}
	else
	{
		return false;
	}
}

