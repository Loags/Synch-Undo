#include "MoveCommand.h"

MoveCommand::MoveCommand(Character* character, Movable::Direction direction) :
	Command(character),
	characterDirection(direction)
{
	characterReversedDirection = character->GetFacingDirection();
}

bool MoveCommand::Execute()
{
	const bool success = character->Move(character->GetGridObject(), characterDirection);
	return success;
}

void MoveCommand::Undo()
{
	ReverseDirection();
	character->Move(character->GetGridObject(), characterReversedDirection);
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

