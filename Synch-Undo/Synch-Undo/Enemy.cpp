#include "Enemy.h"
#include <iostream>
#include <SDL_timer.h>
#include "Grid.h"
#include "ItemManager.h"
#include "RenderComponent.h"


Enemy::Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize) :
	Character(owner, gridObject, offSet, CharacterStats::Enemy, 2, 1, "EnemyComponent"),
	actionDelay(250),
	lastActionTime(0),
	isWaiting(false)
{
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, enemySize, enemySize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 255, 0, 0, 255 });
	owner->AddComponent(renderComponent);

	targetTurnState = GameStateManager::TurnState::EnemyTurn;

	grid = gridObject->GetComponent<Grid>();
	const std::pair<int, int> pos = grid->GetPositionToGridCoords(posX, posY);
	grid->SetCellState(pos.first, pos.second, Cell::Occupied);
}

void Enemy::Update()
{
	Character::Update();
	if (stats.GetIsDead()) return;
	if (GameStateManager::GetCurrentTurnState() != targetTurnState) return;

	const Uint32 currentTime = SDL_GetTicks();

	if (!isWaiting) {
		lastActionTime = currentTime;
		isWaiting = true;
		return;
	}

	if (currentTime - lastActionTime < actionDelay) {
		return;
	}

	isWaiting = false;

	const std::pair<int, int> playerGridPos = grid->GetCharacterGridPosition(CharacterStats::Player);
	const std::pair<int, int> enemyGridPos = grid->GetCharacterGridPosition(CharacterStats::Enemy);

	const Direction playerDirection = DeterminePlayerDirection(playerGridPos, enemyGridPos);

	const std::vector<Movable::Direction> path = grid->FindPathBFS(enemyGridPos, playerGridPos);
	if (!path.empty()) {
		const Movable::Direction nextStep = path[0];
		GameStateManager::SetCurrentTurnState(GameStateManager::TurnState::PlayerTurn);
		if (IsPlayerAdjacent(playerGridPos, enemyGridPos))
		{
			if (!IsFacingPlayer(GetFacingDirection(), playerGridPos, enemyGridPos))
			{
				Rotate(playerDirection);
			}
			else
			{
				Attack();
			}
		}
		else
		{
			Move(gridObject, nextStep);
		}
	}
	else {
		std::cout << "Path is empty!";
	}
}

void Enemy::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Enemy::Die()
{
	const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
	Cell* targetCell = grid->GetCellAtPos(gridPos.first, gridPos.second);
	itemManager->SpawnItemAtCell(targetCell, Interactable::InteractableType::ScorePickUp, 1);

	Character::Die();
}

void Enemy::Respawn()
{
	Character::Respawn();
}

Movable::Direction Enemy::DeterminePlayerDirection(const std::pair<int, int> playerPos, const std::pair<int, int> enemyPos) const
{
	const int dx = playerPos.first - enemyPos.first;
	const int dy = playerPos.second - enemyPos.second;

	if (abs(dy) >= abs(dx))
	{
		if (dy > 0)
		{
			return Direction::South;
		}
		else
		{
			return Direction::North;
		}
	}
	else
	{
		if (dx > 0)
		{
			return Direction::East;
		}
		else
		{
			return Direction::West;
		}
	}
}

bool Enemy::IsPlayerAdjacent(const std::pair<int, int> playerPos, const std::pair<int, int> enemyPos) const
{
	const int dx = abs(playerPos.first - enemyPos.first);
	const int dy = abs(playerPos.second - enemyPos.second);

	return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

bool Enemy::IsFacingPlayer(const Direction enemyFacing, const std::pair<int, int> playerPos, const std::pair<int, int> enemyPos) const
{
	Direction requiredFacing;
	if (playerPos.first > enemyPos.first)
	{
		requiredFacing = Direction::East;
	}
	else if (playerPos.first < enemyPos.first)
	{
		requiredFacing = Direction::West;
	}
	else if (playerPos.second > enemyPos.second)
	{
		requiredFacing = Direction::South;
	}
	else if (playerPos.second < enemyPos.second)
	{
		requiredFacing = Direction::North;
	}
	else {
		return false;
	}

	return enemyFacing == requiredFacing;
}
