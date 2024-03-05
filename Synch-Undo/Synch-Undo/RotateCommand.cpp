#include "RotateCommand.h"

RotateCommand::RotateCommand(Character* character, Movable::Direction direction) :
	MoveCommand(character, direction)
{
}
bool RotateCommand::Execute()
{
	character->SetFacingDirection(characterDirection);
	return true;
}

void RotateCommand::Undo()
{
	ReverseDirection();
	character->SetFacingDirection(characterDirection);
}

std::string RotateCommand::ToString() const
{
	const std::string& charDir = character->directionStrings[static_cast<int>(characterDirection)];
	const std::string& charPrevDir = character->directionStrings[static_cast<int>(characterReversedDirection)];
	std::string output = "RotateCommand: Direction " + charDir + "  |  Previous Direction " + charPrevDir;
	return output;
}
