#include "MoveCommand.h"

#include "Character.h"

MoveCommand::MoveCommand(GameObject* object, Movable::Direction direction, const int prevPosX, const int prevPosY) :
	Command(object),
	prevPosX(prevPosX),
	prevPosY(prevPosY),
	characterDirection(direction)
{
	ReverseDirection();
}

void MoveCommand::Execute()
{
	character = object->GetComponent<Character>();
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	const std::pair<int, int> gridPrevPos = grid->GetPositionToGridCoords(prevPosX, prevPosY);
	prevCell = grid->GetCellAtPos(gridPrevPos.first, gridPrevPos.second);
	newCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void MoveCommand::Undo()
{
	ReverseDirection();
	TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	transformComponent->SetPosition(prevPosX, prevPosY);
	prevCell->SetCellState(Cell::Occupied);
	prevCell->SetCharacterObjectRef(object);
	newCell->SetCellState(Cell::Empty);
	newCell->SetCharacterObjectRef(nullptr);
	character->SetFacingDirection(characterDirection);
}

void MoveCommand::ReverseDirection()
{
	switch (characterDirection) {
	case Movable::Direction::North:
		characterReversedDirection = Movable::Direction::South;
		break;
	case Movable::Direction::South:
		characterReversedDirection = Movable::Direction::North;
		break;
	case Movable::Direction::East:
		characterReversedDirection = Movable::Direction::West;
		break;
	case Movable::Direction::West:
		characterReversedDirection = Movable::Direction::East;
		break;
	}
}

std::string MoveCommand::ToString() const
{
	const std::string& charDir = character->directionStrings[static_cast<int>(characterDirection)];
	const std::string& charPrevDir = character->directionStrings[static_cast<int>(characterReversedDirection)];
	std::string output = "MoveCommand: Direction " + charDir + "  |  Previous Direction " + charPrevDir;
	return output;
}

