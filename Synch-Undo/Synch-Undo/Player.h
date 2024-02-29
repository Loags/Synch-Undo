#pragma once
#include "Attackable.h"
#include "Component.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class GameObject;

class Player : public Component, Movable, Attackable {
private:
	const GameObject* gridObject;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

public:

	Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int playerSize);

#pragma region Component

	void Update() override;
	std::string GetName() const override { return "Player"; }

#pragma endregion Component

#pragma region Movable

	void Move(const GameObject* gridObject, const int deltaX, const int deltaY) const override;

#pragma endregion Movable

#pragma region Attackable

	void Attack(Attackable* target) override;
	void TakeDamage(int damage) override;

#pragma endregion Attackable
};
