#pragma once
#include "Command.h"
class PickUp;
class Cell;

class PickUpCommand : public Command
{
private:
	int pickUpPosX;
	int pickUpPosY;
	Cell* pickUpCell;
	PickUp* pickUp;

public:
	PickUpCommand(GameObject* object);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	PickUpCommand* Clone() const override {
		return new PickUpCommand(*this);
	}
};

