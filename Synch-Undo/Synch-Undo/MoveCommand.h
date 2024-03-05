#pragma once
#include "Movable.h"
#include "Command.h"

class MoveCommand : public Command
{
protected:
	Movable::Direction characterDirection;
	Movable::Direction characterReversedDirection;
public:
	MoveCommand(Character* character, Movable::Direction direction);

	bool Execute() override;
	void Undo() override;
	void ReverseDirection();
	std::string ToString() const override;
};

