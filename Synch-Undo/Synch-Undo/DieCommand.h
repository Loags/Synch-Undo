#pragma once
#include "Command.h"
#include "Grid.h"

class Character;

class DieCommand : public Command
{
private:
	int deathPosX;
	int deathPosY;
	Cell* deathCell;
	Character* character;

public:
	explicit DieCommand(GameObject* object);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	DieCommand* Clone() const override {
		return new DieCommand(*this);
	}
};

