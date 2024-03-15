#pragma once
#include "CommandInvoker.h"
#include "Item.h"
#include "ItemManager.h"

class Player;

class PickUp : public Item
{
private:
	ItemManager* itemManager;
	bool isPickedUp;
	CommandInvoker* commandInvoker;
	int value;
	Player* player;

public:
	PickUp(GameObject* owner, int posX, int posY, int cellSize, ItemManager* itemManager, Cell* cellRef);
	void Update() override;
	void Interact() override;
	void SpawnItem() override;
	bool GetIsPickedUp() const { return isPickedUp; }
	void SetIsPickedUp(bool newIsPickedUp) { isPickedUp = newIsPickedUp; }
	int GetValue() const { return value; }
	void SetValue(int amount) { value = amount; }
};

