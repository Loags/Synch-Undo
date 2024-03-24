#pragma once
#include <vector>

#include "Command.h"
#include "Interactable.h"

class Item;
class Cell;

struct SpawnData {
	int newPosX;
	int newPosY;
	int prevPosX;
	int prevPosY;
	Cell* newCell;
	Cell* prevCell;
	Item* itemPickUp;
	GameObject* prevOwner;
	GameObject* owner;
	Interactable::InteractableType interactableType;
};

class SpawnPickUpCommand : public Command
{
private:
	std::vector<SpawnData> spawnData;

public:
	SpawnPickUpCommand(GameObject* object, const std::vector<SpawnData>& spawnData);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	SpawnPickUpCommand* Clone() const override {
		return new SpawnPickUpCommand(*this);
	}
	CommandType GetType() const override { return CommandType::SwapCommand; }
};

