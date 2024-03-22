#pragma once
#include "Command.h"
#include "Interactable.h"

class Item;
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
	Item* itemPickUp;
	GameObject* prevOwner;
	Interactable::InteractableType interactableType;

public:
	SpawnPickUpCommand(GameObject* object, GameObject* prevOwner, const Interactable::InteractableType interactableType);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	SpawnPickUpCommand* Clone() const override {
		return new SpawnPickUpCommand(*this);
	}
};

