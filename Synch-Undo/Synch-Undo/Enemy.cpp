#include "Enemy.h"
#include <iostream>
#include <SDL_timer.h>
#include "Grid.h"
#include "ItemManager.h"
#include "RenderComponent.h"


Enemy::Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize) :
	Character(owner, gridObject, offSet, CharacterStats::Enemy, 2, 1, "EnemyComponent"),
	actionDelay(750),
	lastActionTime(0),
	isWaiting(false)
{
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
	std::cout << "Path length: " << path.size();
	if (!path.empty()) {
		const Movable::Direction nextStep = path[0];
		GameStateManager::SetCurrentTurnState(GameStateManager::TurnState::PlayerTurn);
		if (IsPlayerAdjacent(playerGridPos, enemyGridPos))
		{
			if (!IsFacingPlayer(GetFacingDirection(), playerGridPos, enemyGridPos))
			{
				Rotate(playerDirection);
				std::cout << "rotate";
			}
			else
			{
				Attack();
				std::cout << "attack";
			}
		}
		else
		{
			Move(gridObject, nextStep);
			std::cout << "move";
		}
	}
	else {
		std::cout << "Path is empty";
		// No path found, consider other strategies (wait, move randomly, etc.)
	}
}

void Enemy::Decision(const std::pair<int, int> playerGridPos, const std::pair<int, int> enemyGridPos, const Movable::Direction playerDirection)
{
	GameStateManager::SetCurrentTurnState(GameStateManager::TurnState::PlayerTurn);
	if (IsPlayerAdjacent(playerGridPos, enemyGridPos))
	{
		if (!IsFacingPlayer(GetFacingDirection(), playerGridPos, enemyGridPos))
		{
			Rotate(playerDirection);
			std::cout << "rotate";
		}
		else
		{
			Attack();
			std::cout << "attack";
		}
	}
	else
	{
		const Direction nextStepDirection = FindNextStepTowardsPlayer(playerGridPos, enemyGridPos);
		Move(gridObject, nextStepDirection);
		std::cout << "move";
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
	itemManager->SpawnPickUpAtCell(targetCell, 1);

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

Enemy::Direction Enemy::FindNextStepTowardsPlayer(std::pair<int, int> playerPos, std::pair<int, int> enemyPos) const
{
	const std::vector<Direction> possibleDirections = { Direction::North, Direction::East, Direction::South, Direction::West };
	Direction bestDirection = Direction::North;
	int shortestDistance = std::numeric_limits<int>::max();

	for (const Direction dir : possibleDirections)
	{
		std::pair<int, int> nextPos = enemyPos;
		switch (dir) {
		case Direction::North: nextPos.second -= 1; break;
		case Direction::South: nextPos.second += 1; break;
		case Direction::East:  nextPos.first += 1; break;
		case Direction::West:  nextPos.first -= 1; break;
		}
		const Cell* targetCell = grid->GetCellAtPos(nextPos.first, nextPos.second);
		if (targetCell->GetCellState() == Cell::Empty || targetCell->GetCellState() == Cell::PickUp)
		{
			const int dx = playerPos.first - nextPos.first;
			const int dy = playerPos.second - nextPos.second;
			const int distance = abs(dx) + abs(dy);
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				bestDirection = dir;
			}
		}
	}

	return bestDirection;
}
