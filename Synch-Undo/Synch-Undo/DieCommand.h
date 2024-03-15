#pragma once
#include "Command.h"
#include "Grid.h"

class PickUp;
class Character;

class DieCommand : public Command
{
private:
	int deathPosX;
	int deathPosY;
	Cell* deathCell;
	Character* character;

	int spawnPosX;
	int spawnPosY;
	Cell* spawnCell;
	PickUp* pickUp;

public:
	explicit DieCommand(GameObject* object);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	DieCommand* Clone() const override {
		return new DieCommand(*this);
	}
};

