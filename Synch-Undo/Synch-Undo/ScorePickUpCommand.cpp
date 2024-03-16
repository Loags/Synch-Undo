#include "ScorePickUpCommand.h"
#include "Player.h"
#include "ScorePickUp.h"
#include "Cell.h"

ScorePickUpCommand::ScorePickUpCommand(GameObject* object, Player* player) :
	PickUpCommand(object, player),
	scorePickUp(nullptr)
{
}


void ScorePickUpCommand::Execute()
{
	scorePickUp = object->GetComponent<ScorePickUp>();
	item = scorePickUp;
	PickUpCommand::Execute();
}

void ScorePickUpCommand::Undo()
{
	PickUpCommand::Undo();
	player->SetScore(-scorePickUp->GetValue());
}

std::string ScorePickUpCommand::ToString() const
{
	std::string output = "ScorePickUp collected at cell: " + std::to_string(itemCell->GetCellPos().first) + "  |  " + std::to_string(itemCell->GetCellPos().second);
	return output;
}
