#pragma once
#include <vector>

#include "Component.h"
#include "Grid.h"
#include "Item.h"

class Cell;
class Grid;

class CommandInvoker;
class PickUp;

class ItemManager : public Component
{
private:
	Grid* gridRef;
	std::vector<PickUp*> pickUpsOnGrid;
	std::vector<Item*> itemsOnGrid;
	CommandInvoker* commandInvoker;

public:
	ItemManager(GameObject* owner);

	void Update() override;
	PickUp* SpawnPickUpAtCell(Cell* targetCell, const int value = 1);
	void SpawnPickUp(int index, bool IsInitialSpawn = false);
	void SpawnPickUps(bool IsInitialSpawn = false);
	bool AllPickUpsCollected() const;
	void NotifyPickUpInteracted();
};

