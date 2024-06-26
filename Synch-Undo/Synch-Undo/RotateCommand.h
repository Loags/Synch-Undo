#pragma once
#include "MoveCommand.h"

class RotateCommand final : public MoveCommand
{
private:
	Character* character;
public:
	RotateCommand(GameObject* object, Movable::Direction direction);

private:
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	RotateCommand* Clone() const override {
		return new RotateCommand(*this);
	}
};

