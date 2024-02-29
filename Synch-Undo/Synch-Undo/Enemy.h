#pragma once
#include "Attackable.h"
#include "Character.h"
#include "Movable.h"



class Enemy : public Character
{
public:

	Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize);


#pragma region Component

	std::string GetName() const override { return "EnemyComponent"; }

#pragma endregion Component

#pragma region Movable

	void Move(const GameObject* gridObject, const Direction newFacingDirection)  override;

#pragma endregion Movable

#pragma region Attackable

	void Die() override;

#pragma endregion Attackable
};
