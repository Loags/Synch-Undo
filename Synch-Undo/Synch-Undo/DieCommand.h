#pragma once
#include "Command.h"
#include "Grid.h"

class DieCommand : public Command
{
private:
	int deathPosX;
	int deathPosY;
	Cell* deathCell;

public:
	explicit DieCommand(Character* character);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

