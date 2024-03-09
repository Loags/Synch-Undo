#include "RespawnCommand.h"
#include <SDL_timer.h>
#include "Character.h"

RespawnCommand::RespawnCommand(GameObject* object) :
	Command(object),
	respawnPosX(0),
	respawnPosY(0),
	respawnCell(nullptr),
	character(nullptr)
{
}

void RespawnCommand::Execute()
{
	character = object->GetComponent<Character>();
	const TransformComponent* transformComponent = object->GetComponent<TransformComponent>();
	respawnPosX = transformComponent->GetX();
	respawnPosY = transformComponent->GetY();
	const Grid* grid = object->GetRootObject()->GetComponentInChildren<Grid>();
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(respawnPosX, respawnPosY);
	respawnCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
}

void RespawnCommand::Undo()
{
	respawnCell->SetCharacterObjectRef(nullptr);
	respawnCell->SetCellState(Cell::Empty);

	character->stats.SetHealth(0);
	character->stats.SetIsDead(true);
	character->GetOwner()->GetComponent<RenderComponent>()->SetVisible(false);
	character->SetPendingRespawn(true);
	character->SetDeathTime(SDL_GetTicks());
}

std::string RespawnCommand::ToString() const
{
	const std::string& characterRespawnType = CharacterStats::CharacterTypeStrings[character->stats.type];

	return "RespawnCommand: Character respawned: " + characterRespawnType;
}
