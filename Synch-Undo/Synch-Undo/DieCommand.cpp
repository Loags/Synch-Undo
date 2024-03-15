#include "DieCommand.h"

#include "Character.h"
#include "PickUp.h"

DieCommand::DieCommand(GameObject* object) :
	Command(object),
	deathPosX(0),
	deathPosY(0),
	deathCell(nullptr),
	character(nullptr),
	spawnPosX(0),
	spawnPosY(0),
	spawnCell(nullptr),
	pickUp(nullptr)
{
}

void DieCommand::Execute()
{
	character = object->GetComponent<Character>();
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	deathPosX = transformComponent->GetX();
	deathPosY = transformComponent->GetY();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(deathPosX, deathPosY);
	deathCell = grid->GetCellAtPos(gridPos.first, gridPos.second);

	pickUp = deathCell->GetOwner()->GetComponentInChildren<PickUp>();
}

void DieCommand::Undo()
{
	if (pickUp && !pickUp->GetIsPickedUp())
	{
		pickUp->SetIsPickedUp(true);
		pickUp->GetOwner()->GetComponent<RenderComponent>()->SetVisible(false);
	}

	deathCell->SetCellState(Cell::Occupied);
	deathCell->SetCharacterObjectRef(object);

	character->SetPendingRespawn(false);
	character->SetDeathTime(0);
	character->GetOwner()->GetComponent<RenderComponent>()->SetVisible(true);
	character->stats.SetIsDead(false);
	character->GetOwner()->GetComponent<TransformComponent>()->SetPosition(deathPosX, deathPosY);
}

std::string DieCommand::ToString() const
{
	const std::string& characterDiedType = CharacterStats::CharacterTypeStrings[character->stats.type];

	return "DieCommand: Character died: " + characterDiedType;
}
