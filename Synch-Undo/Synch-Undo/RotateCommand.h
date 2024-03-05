#pragma once
#include "MoveCommand.h"

class RotateCommand : public MoveCommand
{
public:
	RotateCommand(Character* character, Movable::Direction direction);

private:
	bool Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

