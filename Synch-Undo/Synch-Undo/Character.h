#pragma once
#include "Attackable.h"
#include "Component.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class Character : public Component, public Movable, public Attackable
{
protected:
	const GameObject* gridObject;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	
public:
	Character(GameObject* owner, const GameObject* gridObject, const int offSet, const CharacterStats::CharacterType characterType, const int health, const int damage);
	

#pragma region Component

	void Update() override;

#pragma endregion Component

#pragma region Movable

	void Move(const GameObject* gridObject, const Direction newFacingDirection) override;

#pragma endregion Movable

#pragma region Attackable
	void Attack();
	void Attack(Attackable* target) override;
	void Die() override;
#pragma endregion Attackable


};

