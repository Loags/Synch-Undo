#include "SpawnPickUpCommand.h"

#include "ScorePickUp.h"
#include "HealthPickUp.h"
#include "Player.h"
#include "Grid.h"

SpawnPickUpCommand::SpawnPickUpCommand(GameObject* object, GameObject* prevOwner, const Interactable::InteractableType interactableType) :
	Command(object),
	newPosX(0),
	newPosY(0),
	prevPosX(0),
	prevPosY(0),
	newCell(nullptr),
	prevCell(nullptr),
	itemPickUp(nullptr),
	prevOwner(prevOwner),
	interactableType(interactableType)
{
	SetCommandType(CommandType::Double);
}

void SpawnPickUpCommand::Execute()
{
	switch (interactableType) {
	case Interactable::InteractableType::ScorePickUp:
		itemPickUp = object->GetComponentInChildren<ScorePickUp>();
		break;
	case Interactable::InteractableType::HealthPickUp:
		itemPickUp = object->GetComponentInChildren<HealthPickUp>();
		break;
	}

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
	TransformComponent* pickUpTransform = itemPickUp->GetOwner()->GetComponent<TransformComponent>();
	pickUpTransform->SetPosition(prevPosX, prevPosY);
	itemPickUp->SetCellRef(prevCell);
	itemPickUp->GetOwner()->GetComponent<RenderComponent>()->SetVisible(false);
	itemPickUp->SetInteracted(false);
	//itemPickUp->SpawnItem();
	itemPickUp->GetOwner()->Reparent(prevOwner);
}

std::string SpawnPickUpCommand::ToString() const
{
	std::string output = "Spawned item of type " + Item::InteractableToString(itemPickUp->GetInteractableType()) +
		" at (" + std::to_string(newPosX) + "," + std::to_string(newPosY) + ")";
	return output;
}
