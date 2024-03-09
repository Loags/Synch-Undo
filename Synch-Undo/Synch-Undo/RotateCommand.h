#pragma once
#include "MoveCommand.h"

class RotateCommand : public MoveCommand
{
private:
	Character* character;
public:
	RotateCommand(GameObject* object, Movable::Direction direction);

private:
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

