#pragma once
#include "Component.h"
#include "Grid.h"

class PickUp;

class ItemManager : public Component
{
private:
	Grid* gridRef;
	std::vector<PickUp*> pickUpsOnGrid;

public:
	ItemManager(GameObject* owner);

	void Update() override;
	void SpawnPickUp(int index, bool IsInitialSpawn = false);
	void SpawnPickUps(bool IsInitialSpawn = false);
	bool AllPickUpsCollected() const;
	void NotifyPickUpInteracted();
};

