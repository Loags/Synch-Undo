#pragma once
#include "Attackable.h"
#include "Character.h"
#include "Movable.h"

class GameObject;

class Player : public Character
{
public:
	Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int playerSize);

#pragma region Component

	std::string GetName() const override { return "PlayerComponent"; }

#pragma endregion Component

#pragma region Movable

	void Move(const GameObject* gridObject, const Direction newFacingDirection) override;

#pragma endregion Movable
};
