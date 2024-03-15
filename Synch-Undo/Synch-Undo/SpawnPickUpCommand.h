#pragma once
#include "Command.h"

class PickUp;
class Cell;

class SpawnPickUpCommand : public Command
{
private:
	int newPosX;
	int newPosY;
	int prevPosX;
	int prevPosY;
	Cell* newCell;
	Cell* prevCell;
	PickUp* pickUp;
	GameObject* prevOwner;
public:
	SpawnPickUpCommand(GameObject* object, GameObject* prevOwner);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	SpawnPickUpCommand* Clone() const override {
		return new SpawnPickUpCommand(*this);
	}
};

