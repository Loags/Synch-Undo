#include "ItemManager.h"

#include "ScorePickUp.h"
#include "SpawnPickUpCommand.h"
#include "Player.h"
#include "Enemy.h"
#include "Grid.h"
#include "PickUpCommand.h"
#include "HealthPickUp.h"


class SpawnPickUpCommand;

ItemManager::ItemManager(GameObject* owner) :
	Component("ItemManager", owner)
{
	gridRef = owner->GetComponentInChildren<Grid>();
	commandInvoker = owner->GetComponent<CommandInvoker>();
	scorePickUpsOnGrid.resize(3, nullptr);
	healthPickUpsOnGrid.resize(1, nullptr);
	SpawnPickUps(Interactable::InteractableType::ScorePickUp, 3, true);
	SpawnPickUps(Interactable::InteractableType::HealthPickUp, 1, true);
	owner->GetComponentInChildren<Player>()->SetItemManager(this);
	owner->GetComponentInChildren<Enemy>()->SetItemManager(this);
}

void ItemManager::Update()
{
	if (AllHealthPickUpsCollected())
	{
		std::cout << "test\n";
		SpawnPickUps(Interactable::InteractableType::HealthPickUp, 1, false);
	}

	if (AllScorePickUpsCollected())
	{
		std::cout << "test 2\n";
		SpawnPickUps(Interactable::InteractableType::ScorePickUp, 3, false);
	}
}

Item* ItemManager::SpawnItemAtCell(Cell* targetCell, const Interactable::InteractableType interactableType, const int value)
{
	const int itemPosX = targetCell->GetCellPos().first + gridRef->GetCellSize() / 4;
	const int itemPosY = targetCell->GetCellPos().second + gridRef->GetCellSize() / 4;

	GameObject* itemObject = new GameObject(targetCell->GetOwner(), "ItemObject");
	Item* item = nullptr;

	switch (interactableType) {
	case Interactable::InteractableType::ScorePickUp:
		item = new ScorePickUp(itemObject, itemPosX, itemPosY, gridRef->GetCellSize() / 2, targetCell, value);
		break;
	case Interactable::InteractableType::HealthPickUp:
		item = new HealthPickUp(itemObject, itemPosX, itemPosY, gridRef->GetCellSize() / 2, targetCell, value);
		break;
	}

	if (item) {
		itemObject->AddComponent(item);
		targetCell->SetCellState(Cell::PickUp);
		targetCell->GetOwner()->AddChildGameObject(itemObject);
		itemsOnGrid.push_back(item);
	}

	return item;
}

void ItemManager::SpawnPickUp(int index, const Interactable::InteractableType interactableType, bool IsInitialSpawn)
{
	Cell* emptyCell = gridRef->FindDistantEmptyCell();
	if (emptyCell)
	{
		const int pickUpPosX = emptyCell->GetCellPos().first + gridRef->GetCellSize() / 4;
		const int pickUpPosY = emptyCell->GetCellPos().second + gridRef->GetCellSize() / 4;

		if (IsInitialSpawn) {
			Item* createdItem = SpawnItemAtCell(emptyCell, interactableType, 1);
			switch (interactableType) {
			case Interactable::InteractableType::ScorePickUp: scorePickUpsOnGrid[index] = createdItem; break;
			case Interactable::InteractableType::HealthPickUp: healthPickUpsOnGrid[index] = createdItem; break;
			}
		}
		else
		{
			Item* currentItem = nullptr;
			switch (interactableType) {
			case Interactable::InteractableType::ScorePickUp: currentItem = scorePickUpsOnGrid[index]; break;
			case Interactable::InteractableType::HealthPickUp: currentItem = healthPickUpsOnGrid[index]; break;
			}

			if (currentItem)
			{
				GameObject* prevOwner = currentItem->GetCellRef()->GetOwner();
				TransformComponent* pickUpTransform = currentItem->GetOwner()->GetComponent<TransformComponent>();
				pickUpTransform->SetPosition(pickUpPosX, pickUpPosY);
				currentItem->SpawnItem();
				currentItem->GetOwner()->Reparent(emptyCell->GetOwner());
				currentItem->SetCellRef(emptyCell);
				SpawnPickUpCommand* spawnPickUpCommand = new SpawnPickUpCommand(emptyCell->GetOwner(), prevOwner, interactableType);
				commandInvoker->ExecuteCommand(spawnPickUpCommand);
			}
		}
	}
}

void ItemManager::SpawnPickUps(const Interactable::InteractableType interactableType, const int amount, const bool IsInitialSpawn)
{
	for (int i = 0; i < amount; ++i) {
		SpawnPickUp(i, interactableType, IsInitialSpawn);
	}
}

bool ItemManager::AllScorePickUpsCollected() const
{
	for (const Item* item : scorePickUpsOnGrid)
	{
		if (!item->GetInteracted())
			return false;
	}
	return true;
}

bool ItemManager::AllHealthPickUpsCollected() const
{
	for (const Item* item : healthPickUpsOnGrid)
	{
		if (!item->GetInteracted())
			return false;
	}
	return true;
}