#pragma once
#include "Command.h"
class Player;
class PickUp;
class Cell;

class PickUpCommand final : public Command
{
protected:
	int pickUpPosX;
	int pickUpPosY;
	Cell* pickUpCell;
	PickUp* pickUp;
	Player* player;

public:
	PickUpCommand(GameObject* object, Player* player);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	PickUpCommand* Clone() const override {
		return new PickUpCommand(*this);
	}
};

