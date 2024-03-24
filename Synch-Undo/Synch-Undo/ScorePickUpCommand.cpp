#include "ScorePickUpCommand.h"
#include "Player.h"
#include "ScorePickUp.h"
#include "Cell.h"
#include "Grid.h"

ScorePickUpCommand::ScorePickUpCommand(GameObject* object, Player* player) :
	PickUpCommand(object, player),
	scorePickUp(nullptr)
{
	SetUndoSteps(2);
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
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(itemCell->GetCellPos().first,
		itemCell->GetCellPos().second);
	std::string output = "ScorePickUp collected at cell: " + std::to_string(gridPos.first) + "  |  " + std::to_string(gridPos.second);
	return output;
}
