#pragma once
#include "Movable.h"
#include "Character.h"
#include "Command.h"

class MoveCommand : public Command
{
	Character* character;
	Movable::Direction characterDirection;
	Movable::Direction characterPreviousDirection;
public:
	MoveCommand(Character* character, Movable::Direction direction);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

