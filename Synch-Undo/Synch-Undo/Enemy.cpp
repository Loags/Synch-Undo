#include "Enemy.h"

#include <iostream>
#include <SDL_timer.h>
#include "Grid.h"
#include "RenderComponent.h"


Enemy::Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize) :
	Character(owner, gridObject, offSet, CharacterStats::Enemy, 2, 1, "EnemyComponent") {
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, enemySize, enemySize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 255, 0, 0, 255 });
	owner->AddComponent(renderComponent);

	keyMap = {
			{SDLK_UP, Direction::North},
			{SDLK_DOWN, Direction::South},
			{SDLK_LEFT, Direction::West},
			{SDLK_RIGHT, Direction::East}
	};
	attackKey = SDLK_RETURN;
}

void Enemy::Update()
{
	if (pendingRespawn && SDL_GetTicks() - deathTime >= 5000) {
		Respawn();
		pendingRespawn = false;
	}
}

void Enemy::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Enemy::Die()
{
	Character::Die();
	pendingRespawn = true;
	renderComponent->SetVisible(false);
}

void Enemy::Respawn()
{
	Character::Respawn();
	const Grid* grid = gridObject->GetComponent<Grid>();
	Cell* cell = grid->FindDistantEmptyCell();
	if (!cell) return;
	cell->SetCellState(Cell::Occupied);
	cell->SetCharacterObjectRef(owner);
	transformComponent->SetPosition(cell->GetCellPos().first + offSet, cell->GetCellPos().second + offSet);
	renderComponent->SetVisible(true);
}
