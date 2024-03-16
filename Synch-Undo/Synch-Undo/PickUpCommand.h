#pragma once
#include "Command.h"

class Item;
class Player;
class Cell;

class PickUpCommand : public Command
{
protected:
	int itemPosX;
	int itemPosY;
	Cell* itemCell;
	Item* item;
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

