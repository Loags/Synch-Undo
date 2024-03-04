#include "MoveCommand.h"

MoveCommand::MoveCommand(Character* character, Movable::Direction direction) :
	character(character),
	characterDirection(direction)
{
	characterPreviousDirection = character->GetFacingDirection();
}

void MoveCommand::Execute()
{
	character->Move(character->GetGridObject(), characterDirection);
}

void MoveCommand::Undo()
{
	character->Move(character->GetGridObject(), characterPreviousDirection);
}

std::string MoveCommand::ToString() const
{
	return "MoveCommand: Direction " + static_cast<int>(characterDirection);
}
