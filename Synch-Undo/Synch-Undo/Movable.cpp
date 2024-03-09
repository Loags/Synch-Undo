#include "Movable.h"

#include "Character.h"
#include "Grid.h"
#include "MoveCommand.h"
#include "RotateCommand.h"
#include "TransformComponent.h"

Movable::Movable(const GameObject* movableOwner, const int offSet) :
	offSet(offSet),
	movableOwner(movableOwner),
	facingDirection(Direction::South),
	character(nullptr),
	commandInvoker(nullptr)
{
}

void Movable::SetCharacter(Character* character)
{
	this->character = character;
	commandInvoker = character->GetCommandInvoker();
}


void Movable::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	const Grid* grid = gridObject->GetComponent<Grid>();
	const int cellSize = grid->GetCellSize();

	TransformComponent* transform = movableOwner->GetComponent<TransformComponent>();

	int newPosX = transform->GetX();
	int newPosY = transform->GetY();
	const int prevPosX = newPosX;
	const int prevPosY = newPosY;

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

	if (targetCell == nullptr) return;

	if (targetCell->GetCellState() == Cell::Empty || targetCell->GetCellState() == Cell::PickUp) {
		currentCell->SetCellState(Cell::Empty);
		currentCell->SetCharacterObjectRef(nullptr);

		targetCell->SetCellState(Cell::Occupied);
		targetCell->SetCharacterObjectRef(movableOwner);

		transform->SetPosition(newPosX, newPosY);
		SetFacingDirection(newFacingDirection);

		MoveCommand* moveCommand = new MoveCommand(character->GetOwner(), newFacingDirection, prevPosX, prevPosY);
		commandInvoker->ExecuteCommand(moveCommand);
	}
}

void Movable::Rotate(const Direction newFacingDirection)
{
	SetFacingDirection(newFacingDirection);
	RotateCommand* rotateCommand = new RotateCommand(character->GetOwner(), newFacingDirection);
	commandInvoker->ExecuteCommand(rotateCommand);
}

