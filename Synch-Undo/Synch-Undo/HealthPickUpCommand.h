#pragma once
#include "PickUpCommand.h"

class HealthPickUp;

class HealthPickUpCommand : public PickUpCommand
{
private:
	HealthPickUp* healthPickUp;
	int previousHealth;

public:
	HealthPickUpCommand(GameObject* object, Player* player, const int previousHealth);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

