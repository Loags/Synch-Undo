#pragma once
#include "Attackable.h"
#include "Character.h"
#include "Movable.h"


class Enemy : public Character
{
public:


	Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize);
	~Enemy() override = default;
	void Update() override;
	void Move(const GameObject* gridObject, const Direction newFacingDirection)  override;
	void Die() override;
	void Respawn() override;
};
