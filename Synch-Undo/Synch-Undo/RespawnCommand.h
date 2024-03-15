#pragma once
#include "Command.h"
#include "Grid.h"

class Character;

class RespawnCommand final : public Command
{
private:
	int respawnPosX;
	int respawnPosY;
	Cell* respawnCell;
	Character* character;

public:
	explicit RespawnCommand(GameObject* object);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	RespawnCommand* Clone() const override {
		return new RespawnCommand(*this);
	}
};

