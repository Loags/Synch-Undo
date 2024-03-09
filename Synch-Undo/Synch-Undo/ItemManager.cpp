#include "ItemManager.h"

#include "PickUp.h"

class Player;
class Enemy;

ItemManager::ItemManager(GameObject* owner) :
	Component("ItemManager", owner)
{
	gridRef = owner->GetComponentInChildren<Grid>();
	SpawnPickUps(true);
}

void ItemManager::Update()
{

}

void ItemManager::SpawnPickUp(int index, bool IsInitialSpawn)
{
	Cell* emptyCell = gridRef->FindDistantEmptyCell();
	if (emptyCell)
	{
		const int pickUpPosX = emptyCell->GetCellPos().first + gridRef->GetCellSize() / 4;
		const int pickUpPosY = emptyCell->GetCellPos().second + gridRef->GetCellSize() / 4;

		if (IsInitialSpawn) {
			GameObject* pickUpObject = new GameObject(emptyCell->GetOwner(), "ItemObject");
			PickUp* pickUp = new PickUp(pickUpObject, pickUpPosX, pickUpPosY, gridRef->GetCellSize() / 2, this, emptyCell);
			pickUpObject->AddComponent(pickUp);
			emptyCell->SetCellState(Cell::PickUp);
			pickUpsOnGrid.push_back(pickUp);
			emptyCell->GetOwner()->AddChildGameObject(pickUpObject);
		}
		else
		{
			PickUp* currentPickUp = pickUpsOnGrid[index];
			TransformComponent* pickUpTransform = currentPickUp->GetOwner()->GetComponent<TransformComponent>();
			pickUpTransform->SetPosition(pickUpPosX, pickUpPosY);
			currentPickUp->SpawnItem();
			currentPickUp->GetOwner()->Reparent(emptyCell->GetOwner());
			currentPickUp->SetCellRef(emptyCell);
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
