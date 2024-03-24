#include "Character.h"
#include <SDL_timer.h>
#include "Grid.h"

Character::Character(GameObject* owner, const GameObject* gridObject, const int offSet,
	const CharacterType characterType, const int health, const int damage,
	const std::string& componentName) :
	Component(componentName, owner),
	Movable(owner, offSet),
	Attackable(characterType),
	CharacterStats(health, damage, characterType),
	gridObject(gridObject),
	transformComponent(nullptr),
	renderComponent(nullptr),
	itemManager(nullptr)
{
	commandInvoker = GetOwner()->GetRootObject()->GetComponent<CommandInvoker>();
	grid = gridObject->GetComponent<Grid>();
	CharacterController::SetCharacter(this);
	Attackable::SetCharacter(this);
	Movable::SetCharacter(this);
	EquipmentManager::SetCharacter(this);
}

void Character::Update()
{
	if (GetPendingRespawn() && SDL_GetTicks() - GetDeathTime() >= 1000) {
		Respawn();
		SetPendingRespawn(false);
	}
}

void Character::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Movable::Move(gridObject, newFacingDirection);
}

Character* Character::Attack()
{
	const int cellSize = grid->GetCellSize();

	int attackPosX = 0;
	int attackPosY = 0;

	switch (GetFacingDirection()) {
	case Direction::North: attackPosY -= cellSize; break;
	case Direction::South: attackPosY += cellSize; break;
	case Direction::East:  attackPosX += cellSize; break;
	case Direction::West:  attackPosX -= cellSize; break;
	}

	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX() + attackPosX, transformComponent->GetY() + attackPosY);
	const Cell* targetCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
	const GameObject* targetObject = targetCell->GetCharacterObjectRef();
	if (targetObject)
	{
		Character* targetCharacter = targetObject->GetComponent<Character>();
		lastAttackTarget = targetCharacter;
		Attack(targetCharacter);
		return targetCharacter;
	}
	lastAttackTarget = nullptr;
	return nullptr;
}

void Character::Attack(Attackable* target)
{
	Attackable::Attack(target);
}

void Character::Die()
{
	SetDeathTime(SDL_GetTicks());
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	Cell* cell = grid->GetCellAtPos(gridPos.first, gridPos.second);
	cell->SetCellState(Cell::Empty);
	cell->SetCharacterObjectRef(nullptr);
	pendingRespawn = true;
	renderComponent->SetVisible(false);
	Attackable::Die();
}

void Character::Respawn()
{
	SetCurrentHealth(GetMaxValueOfAttributeType(Attributes::Health));
	SetIsDead(false);
	Cell* cell = grid->FindDistantEmptyCell();
	if (!cell) return;
	cell->SetCellState(Cell::Occupied);
	cell->SetCharacterObjectRef(owner);
	transformComponent->SetPosition(cell->GetCellPos().first + offSet, cell->GetCellPos().second + offSet);
	renderComponent->SetVisible(true);
	Attackable::Respawn();
}
