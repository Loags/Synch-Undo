#pragma once
#include "Movable.h"
#include "Command.h"
#include "Grid.h"

class MoveCommand : public Command
{
private:
	int prevPosX;
	int prevPosY;
	Cell* prevCell;
	Cell* newCell;

protected:
	Movable::Direction characterDirection;
	Movable::Direction characterReversedDirection;
public:
	MoveCommand(Character* character, Movable::Direction direction, const int prevPosX, const int prevPosY);

	void Execute() override;
	void Undo() override;
	void ReverseDirection();
	std::string ToString() const override;
};

