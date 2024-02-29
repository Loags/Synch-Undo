#pragma once
#include "Component.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"


class Enemy : public Component, Movable
{
private:
	const GameObject* gridObject;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

public:

	Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize);


#pragma region Component

	void Update() override;
	std::string GetName() const override { return "Enemy"; }

#pragma endregion Component

#pragma region Movable

	void Move(const GameObject* gridObject, const int deltaX, const int deltaY) const override;

#pragma endregion Movable
};
