#pragma once
#include "Attackable.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class Character :public Component, public Movable, public Attackable
{
protected:
	const GameObject* gridObject;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	Uint32 deathTime = 0;
	bool pendingRespawn = false;

public:
	Character(GameObject* owner, const GameObject* gridObject, const int offSet, const CharacterStats::CharacterType characterType, const int health, const int damage, const std::string& componentName);
	~Character() override = default;
	void Update() override;
	void Move(const GameObject* gridObject, const Direction newFacingDirection) override;
	void Attack();
	void Attack(Attackable* target) override;
	void Die() override;
	void Respawn() override;
};

