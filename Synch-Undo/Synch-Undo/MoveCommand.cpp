#include "MoveCommand.h"

MoveCommand::MoveCommand(Character* character, Movable::Direction direction, const int prevPosX, const int prevPosY) :
	Command(character),
	prevPosX(prevPosX),
	prevPosY(prevPosY),
	characterDirection(direction)
{
	ReverseDirection();
}

void MoveCommand::Execute()
{
	const TransformComponent* transformComponent = character->GetOwner()->GetComponent<TransformComponent>();
	const Grid* grid = character->GetGridObject()->GetComponent<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	const std::pair<int, int> gridPrevPos = grid->GetPositionToGridCoords(prevPosX, prevPosY);
	prevCell = grid->GetCellAtPos(gridPrevPos.first, gridPrevPos.second);
	newCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void MoveCommand::Undo()
{
	ReverseDirection();
	TransformComponent* transformComponent = character->GetOwner()->GetComponent<TransformComponent>();
	transformComponent->SetPosition(prevPosX, prevPosY);
	prevCell->SetCellState(Cell::Occupied);
	newCell->SetCellState(Cell::Empty);
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

