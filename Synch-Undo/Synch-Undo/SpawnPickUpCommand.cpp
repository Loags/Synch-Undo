#include "SpawnPickUpCommand.h"

#include <sstream>
#include "Player.h"
#include "Grid.h"

SpawnPickUpCommand::SpawnPickUpCommand(GameObject* object, const std::vector<SpawnData>& spawnData) :
	Command(object),
	spawnData(spawnData)
{
	//SetUndoSteps(3);
}

void SpawnPickUpCommand::Execute()
{
	for (SpawnData& data : spawnData) {
		const TransformComponent* transformComponent = data.owner->GetComponent<TransformComponent>();
		const Grid* grid = data.owner->GetRootObject()->GetComponentInChildren<Grid>();
		data.newPosX = transformComponent->GetX();
		data.newPosY = transformComponent->GetY();

		data.prevPosX = data.prevCell->GetCellPos().first + grid->GetCellSize() / 4;
		data.prevPosY = data.prevCell->GetCellPos().second + grid->GetCellSize() / 4;
	}
}

void SpawnPickUpCommand::Undo()
{
	for (const SpawnData& data : spawnData) {
		TransformComponent* pickUpTransform = data.itemPickUp->GetOwner()->GetComponent<TransformComponent>();
		pickUpTransform->SetPosition(data.prevPosX, data.prevPosY);
		data.itemPickUp->SetCellRef(data.prevCell);
		data.itemPickUp->GetOwner()->Reparent(data.prevOwner);

		if (data.itemPickUp->GetInteractableType() == Interactable::InteractableType::HealthPickUp)
		{
			data.itemPickUp->SetInteracted(false);
			data.itemPickUp->GetOwner()->GetComponent<RenderComponent>()->SetVisible(true);
		}
		if (data.itemPickUp->GetInteractableType() == Interactable::InteractableType::ScorePickUp)
		{
			data.itemPickUp->SetInteracted(true);
			data.itemPickUp->GetOwner()->GetComponent<RenderComponent>()->SetVisible(false);
		}

		data.itemPickUp->GetOwner()->Reparent(data.prevOwner);
	}
}

std::string SpawnPickUpCommand::ToString() const
{
	std::stringstream output;
	output << "SpawnPickUpCommand with " << spawnData.size() << " items:\n";

	for (const SpawnData& data : spawnData) {
		const std::pair<int, int> newGridPos = data.owner->GetRootObject()->GetComponentInChildren<Grid>()->
			GetPositionToGridCoords(data.newPosX, data.newPosY);
		const std::pair<int, int> prevGridPos = data.prevOwner->GetRootObject()->GetComponentInChildren<Grid>()->
			GetPositionToGridCoords(data.prevPosX, data.prevPosY);

		output << "Item of type " << Item::InteractableToString(data.interactableType)
			<< " - New Grid Pos: (" << newGridPos.first << ", " << newGridPos.second << "), "
			<< "Old Grid Pos: (" << prevGridPos.first << ", " << prevGridPos.second << "), "
			<< "Undo Grid Pos: (" << prevGridPos.first << ", " << prevGridPos.second << ")\n";
	}

	return output.str();
}
