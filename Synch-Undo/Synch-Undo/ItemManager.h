#pragma once
#include <vector>
#include "Component.h"
#include "Item.h"

class HealthPickUp;
class ScorePickUp;
class Cell;
class Grid;
class CommandInvoker;


class ItemManager : public Component
{
private:
	Grid* gridRef;
	std::vector<Item*> scorePickUpsOnGrid;
	std::vector<Item*> healthPickUpsOnGrid;
	std::vector<Item*> itemsOnGrid;
	CommandInvoker* commandInvoker;

public:
	ItemManager(GameObject* owner);

	void Update() override;
	Item* SpawnItemAtCell(Cell* targetCell, const Interactable::InteractableType interactableType, const int value = 1);

private:
	Item* SpawnPickUp(int index, Cell* targetCell, const Interactable::InteractableType interactableType, bool IsInitialSpawn = false);
	void SpawnPickUps(const Interactable::InteractableType interactableType, const int amount, const bool IsInitialSpawn = false);
	bool AllScorePickUpsCollected() const;
	bool AllHealthPickUpsCollected() const;

};

