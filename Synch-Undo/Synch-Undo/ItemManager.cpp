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
		SpawnPickUps(Interactable::InteractableType::HealthPickUp, 1, false);
	}

	if (AllScorePickUpsCollected())
	{
		SpawnPickUps(Interactable::InteractableType::ScorePickUp, 3, false);
	}
}

Item* ItemManager::SpawnItemAtCell(Cell* targetCell, const Interactable::InteractableType interactableType, const int value)
{
	//TODO: Handle edge case when a pickup is already inside a cell and the enemy dies and spawns a ScorePickUp!

	const int itemPosX = targetCell->GetCellPos().first + gridRef->GetCellSize() / 4;
	const int itemPosY = targetCell->GetCellPos().second + gridRef->GetCellSize() / 4;

	GameObject* itemObject = new GameObject(targetCell->GetOwner(), "ItemObject");
	Item* item = nullptr;

	switch (interactableType) {
	case Interactable::InteractableType::ScorePickUp:
		item = new ScorePickUp(itemObject, itemPosX, itemPosY, gridRef->GetCellSize() / 2, targetCell, value);
		break;
	case Interactable::InteractableType::HealthPickUp:
		item = new HealthPickUp(itemObject, itemPosX, itemPosY, gridRef->GetCellSize() / 2, targetCell, 25);
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

Item* ItemManager::SpawnPickUp(int index, Cell* targetCell, const Interactable::InteractableType interactableType, bool IsInitialSpawn)
{
	if (targetCell)
	{
		const int pickUpPosX = targetCell->GetCellPos().first + gridRef->GetCellSize() / 4;
		const int pickUpPosY = targetCell->GetCellPos().second + gridRef->GetCellSize() / 4;

		if (IsInitialSpawn) {
			Item* createdItem = SpawnItemAtCell(targetCell, interactableType, 1);
			switch (interactableType) {
			case Interactable::InteractableType::ScorePickUp: scorePickUpsOnGrid[index] = createdItem; break;
			case Interactable::InteractableType::HealthPickUp: healthPickUpsOnGrid[index] = createdItem; break;
			}
			return createdItem;
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
				currentItem->GetOwner()->Reparent(targetCell->GetOwner());
				currentItem->SetCellRef(targetCell);
				return currentItem;
			}
		}
	}
	return nullptr;
}

void ItemManager::SpawnPickUps(const Interactable::InteractableType interactableType, const int amount, const bool IsInitialSpawn)
{
	std::vector<SpawnData> allSpawnData;

	for (int i = 0; i < amount; ++i) {
		Cell* targetCell = gridRef->FindDistantEmptyCell();

		if (!targetCell)continue;

		SpawnData data;

		if (!IsInitialSpawn)
		{
			Item* prevItem = nullptr;
			switch (interactableType) {
			case Interactable::InteractableType::ScorePickUp: prevItem = scorePickUpsOnGrid[i]; break;
			case Interactable::InteractableType::HealthPickUp: prevItem = healthPickUpsOnGrid[i]; break;
			}
			data.prevCell = prevItem->GetCellRef();
			data.prevOwner = data.prevCell->GetOwner();
			data.newCell = targetCell;
			data.interactableType = interactableType;
		}

		Item* currentItem = SpawnPickUp(i, targetCell, interactableType, IsInitialSpawn);

		if (!IsInitialSpawn)
		{
			data.owner = targetCell->GetOwner();
			data.itemPickUp = currentItem;
			allSpawnData.push_back(data);
		}
	}

	if (!allSpawnData.empty() && !IsInitialSpawn)
	{
		SpawnPickUpCommand* spawnPickUpCommand = new SpawnPickUpCommand(owner, allSpawnData);
		commandInvoker->ExecuteCommand(spawnPickUpCommand);
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