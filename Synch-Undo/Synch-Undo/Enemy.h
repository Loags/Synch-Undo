#pragma once
#include "Character.h"
#include "Movable.h"

class Enemy final : public Character
{
private:
	Uint32 actionDelay;
	Uint32 lastActionTime;
	bool isWaiting;

public:
	Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize);
	~Enemy() override = default;
	void Update() override;
	void Move(const GameObject* gridObject, const Direction newFacingDirection)  override;
	void Die() override;
	void Respawn() override;
	Direction DeterminePlayerDirection(const std::pair<int, int> playerPos, const std::pair<int, int> enemyPos) const;
	bool IsPlayerAdjacent(const std::pair<int, int> playerPos, const std::pair<int, int> enemyPos) const;
	bool IsFacingPlayer(Direction enemyFacing, std::pair<int, int> playerPos, std::pair<int, int> enemyPos) const;
	Direction FindNextStepTowardsPlayer(std::pair<int, int> playerPos, std::pair<int, int> enemyPos) const;
};
