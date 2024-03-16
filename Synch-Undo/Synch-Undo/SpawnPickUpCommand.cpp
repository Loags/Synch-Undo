#include "SpawnPickUpCommand.h"

#include "ScorePickUp.h"
#include "Player.h"
#include "Grid.h"

SpawnPickUpCommand::SpawnPickUpCommand(GameObject* object, GameObject* prevOwner) :
	Command(object),
	newPosX(0),
	newPosY(0),
	prevPosX(0),
	prevPosY(0),
	newCell(nullptr),
	prevCell(nullptr),
	pickUp(nullptr),
	prevOwner(prevOwner)
{

}

void SpawnPickUpCommand::Execute()
{
	pickUp = object->GetComponentInChildren<ScorePickUp>();
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	newPosX = transformComponent->GetX();
	newPosY = transformComponent->GetY();
	newCell = grid->GetCellAtPos(gridPos.first, gridPos.second);

	prevCell = prevOwner->GetComponent<Cell>();
	prevPosX = prevCell->GetCellPos().first + grid->GetCellSize() / 4;
	prevPosY = prevCell->GetCellPos().second + grid->GetCellSize() / 4;
	const GameObject* objectRef = prevCell->GetCharacterObjectRef();
	if (objectRef)
		if (objectRef->GetComponent<Player>())
			SetCommandType(CommandType::Double);
}

void SpawnPickUpCommand::Undo()
{
	TransformComponent* pickUpTransform = pickUp->GetOwner()->GetComponent<TransformComponent>();
	pickUpTransform->SetPosition(prevPosX, prevPosY);
	pickUp->SetCellRef(prevCell);
	pickUp->GetOwner()->GetComponent<RenderComponent>()->SetVisible(false);
	pickUp->SetInteracted(false);
	//pickUp->SpawnItem();
	pickUp->GetOwner()->Reparent(prevOwner);
}

std::string SpawnPickUpCommand::ToString() const
{
	return "output";
}
