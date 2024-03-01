#include "Character.h"

#include <SDL_timer.h>

#include "Grid.h"

Character::Character(GameObject* owner, const GameObject* gridObject, const int offSet,
	const CharacterStats::CharacterType characterType, const int health, const int damage,
	const std::string& componentName) :
	Component(componentName, owner),
	Movable(owner, offSet),
	Attackable(health, damage, characterType),
	gridObject(gridObject),
	transformComponent(nullptr),
	renderComponent(nullptr)
{
}

void Character::Update()
{
}

void Character::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Movable::Move(gridObject, newFacingDirection);
}

void Character::Attack()
{
	const Grid* grid = gridObject->GetComponent<Grid>();
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
		Attack(targetCharacter);
	}
}

void Character::Attack(Attackable* target)
{
	Attackable::Attack(target);
}

void Character::Die()
{
	Attackable::Die();
	deathTime = SDL_GetTicks();
	Grid* grid = gridObject->GetComponent<Grid>();
	std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	Cell* cell = grid->GetCellAtPos(gridPos.first, gridPos.second);
	cell->SetCellState(Cell::Empty);
	cell->SetCharacterObjectRef(nullptr);
}

void Character::Respawn()
{
	Attackable::Respawn();
	stats.SetHealth(stats.GetInitialHealth());
	stats.SetisDead(false);
}
