#include "RotateCommand.h"

#include "Character.h"

RotateCommand::RotateCommand(GameObject* object, Movable::Direction direction) :
	MoveCommand(object, direction, 0, 0)
{
}
void RotateCommand::Execute()
{
	character = object->GetComponent<Character>();
	character->SetFacingDirection(characterDirection);
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
