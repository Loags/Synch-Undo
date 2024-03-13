#include "PickUpCommand.h"
#include "Grid.h"
#include "PickUp.h"
#include "Player.h"

PickUpCommand::PickUpCommand(GameObject* object) :
	Command(object),
	pickUpPosX(0),
	pickUpPosY(0),
	pickUpCell(nullptr),
	pickUp(nullptr)
{
	SetCommandType(CommandType::Double);
}

void PickUpCommand::Execute()
{
	pickUp = object->GetComponent<PickUp>();
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	pickUpPosX = transformComponent->GetX();
	pickUpPosY = transformComponent->GetY();
	pickUpCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void PickUpCommand::Undo()
{
	pickUpCell->SetCellState(Cell::PickUp);

	pickUp->SetIsPickedUp(false);

	object->GetComponent<RenderComponent>()->SetVisible(true);
}

std::string PickUpCommand::ToString() const
{
	std::string output = "PickUp collected at cell: " + std::to_string(pickUpCell->GetCellPos().first) + "  |  " + std::to_string(pickUpCell->GetCellPos().second);
	return output;
}
