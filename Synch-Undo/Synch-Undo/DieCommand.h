#pragma once
#include "Command.h"
#include "Grid.h"

class ScorePickUp;
class Character;

class DieCommand final : public Command
{
private:
	int deathPosX;
	int deathPosY;
	Cell* deathCell;
	Character* character;

	int spawnPosX;
	int spawnPosY;
	Cell* spawnCell;
	ScorePickUp* pickUp;

public:
	explicit DieCommand(GameObject* object);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	DieCommand* Clone() const override {
		return new DieCommand(*this);
	}
};

