#include "DieCommand.h"

DieCommand::DieCommand(Character* character) :
	Command(character),
	deathPosX(0),
	deathPosY(0),
	deathCell(nullptr)
{
}

void DieCommand::Execute()
{
	const TransformComponent* transformComponent = character->GetOwner()->GetComponent<TransformComponent>();
	deathPosX = transformComponent->GetX();
	deathPosY = transformComponent->GetY();
	const Grid* grid = character->GetGridObject()->GetComponent<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(deathPosX, deathPosY);
	deathCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void DieCommand::Undo()
{
	deathCell->SetCellState(Cell::Occupied);
	deathCell->SetCharacterObjectRef(character->GetOwner());

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
