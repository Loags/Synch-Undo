#include "PickUpCommand.h"
#include "Grid.h"
#include "HealthPickUp.h"
#include "Player.h"

PickUpCommand::PickUpCommand(GameObject* object, Player* player) :
	Command(object),
	itemPosX(0),
	itemPosY(0),
	itemCell(nullptr),
	item(nullptr),
	player(player)
{
	SetCommandType(CommandType::Double);
}

void PickUpCommand::Execute()
{
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	itemPosX = transformComponent->GetX();
	itemPosY = transformComponent->GetY();
	itemCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void PickUpCommand::Undo()
{
	itemCell->SetCellState(Cell::PickUp);
	item->SetInteracted(false);
	object->GetComponent<RenderComponent>()->SetVisible(true);
}

std::string PickUpCommand::ToString() const
{
	return "";
}
