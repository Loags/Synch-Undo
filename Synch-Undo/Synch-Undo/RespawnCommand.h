#pragma once
#include "Command.h"
#include "Grid.h"

class RespawnCommand : public Command
{
private:
	int respawnPosX;
	int respawnPosY;
	Cell* respawnCell;

public:
	explicit RespawnCommand(Character* character);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

