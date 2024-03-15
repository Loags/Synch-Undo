#include "ItemManager.h"

#include "PickUp.h"
#include "SpawnPickUpCommand.h"
#include "Player.h"
#include "Enemy.h"
#include "PickUpCommand.h"


class SpawnPickUpCommand;

ItemManager::ItemManager(GameObject* owner) :
	Component("ItemManager", owner)
{
	gridRef = owner->GetComponentInChildren<Grid>();
	commandInvoker = owner->GetComponent<CommandInvoker>();
	SpawnPickUps(true);
	owner->GetComponentInChildren<Player>()->SetItemManager(this);
	owner->GetComponentInChildren<Enemy>()->SetItemManager(this);
}

void ItemManager::Update()
{

}

PickUp* ItemManager::SpawnPickUpAtCell(Cell* targetCell, const int value)
{
	const int pickUpPosX = targetCell->GetCellPos().first + gridRef->GetCellSize() / 4;
	const int pickUpPosY = targetCell->GetCellPos().second + gridRef->GetCellSize() / 4;

	GameObject* pickUpObject = new GameObject(targetCell->GetOwner(), "PickUpObject");
	PickUp* pickUp = new PickUp(pickUpObject, pickUpPosX, pickUpPosY, gridRef->GetCellSize() / 2, this, targetCell);
	pickUp->SetValue(value);
	pickUpObject->AddComponent(pickUp);
	targetCell->SetCellState(Cell::PickUp);
	targetCell->GetOwner()->AddChildGameObject(pickUpObject);

	return pickUp;
}

void ItemManager::SpawnPickUp(int index, bool IsInitialSpawn)
{
	Cell* emptyCell = gridRef->FindDistantEmptyCell();
	if (emptyCell)
	{
		const int pickUpPosX = emptyCell->GetCellPos().first + gridRef->GetCellSize() / 4;
		const int pickUpPosY = emptyCell->GetCellPos().second + gridRef->GetCellSize() / 4;

		if (IsInitialSpawn) {
			PickUp* createdPickUp = SpawnPickUpAtCell(emptyCell, 1);
			pickUpsOnGrid.push_back(createdPickUp);
			itemsOnGrid.push_back(createdPickUp);
		}
		else
		{
			PickUp* currentPickUp = pickUpsOnGrid[index];
			GameObject* prevOwner = currentPickUp->GetCellRef()->GetOwner();
			TransformComponent* pickUpTransform = currentPickUp->GetOwner()->GetComponent<TransformComponent>();
			pickUpTransform->SetPosition(pickUpPosX, pickUpPosY);
			currentPickUp->SpawnItem();
			currentPickUp->GetOwner()->Reparent(emptyCell->GetOwner());
			currentPickUp->SetCellRef(emptyCell);
			SpawnPickUpCommand* spawnPickUpCommand = new SpawnPickUpCommand(emptyCell->GetOwner(), prevOwner);
			commandInvoker->ExecuteCommand(spawnPickUpCommand);
		}
	}
}

void ItemManager::SpawnPickUps(bool IsInitialSpawn)
{
	for (int i = 0; i < 3; ++i) {
		SpawnPickUp(i, IsInitialSpawn);
	}
}

bool ItemManager::AllPickUpsCollected() const
{
	for (const PickUp* pickUp : pickUpsOnGrid)
	{
		if (!pickUp->GetIsPickedUp())
			return false;
	}
	return true;
}

void ItemManager::NotifyPickUpInteracted()
{
	if (AllPickUpsCollected())
		SpawnPickUps(false);
}
