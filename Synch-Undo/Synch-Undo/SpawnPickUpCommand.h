#pragma once
#include "Command.h"

class ScorePickUp;
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
	ScorePickUp* pickUp;
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

