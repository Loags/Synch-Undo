#include "HealthPickUpCommand.h"
#include "HealthPickUp.h"
#include "Player.h"

HealthPickUpCommand::HealthPickUpCommand(GameObject* object, Player* player, const int previousHealth) :
	PickUpCommand(object, player),
	healthPickUp(nullptr),
	previousHealth(previousHealth)
{
}

void HealthPickUpCommand::Execute()
{
	healthPickUp = object->GetComponent<HealthPickUp>();
	item = healthPickUp;
	PickUpCommand::Execute();
}

void HealthPickUpCommand::Undo()
{
	PickUpCommand::Undo();
	player->stats.SetHealth(previousHealth);
}

std::string HealthPickUpCommand::ToString() const
{
	return PickUpCommand::ToString();
}
