#include "Player.h"
#include <iostream>
#include "RenderComponent.h"


Player::Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet,
	const int playerSize) :
	Component(owner),
	Movable(owner, offSet),
	gridObject(gridObject)
{
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, playerSize,
		playerSize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 0, 255, 0, 255 });
	owner->AddComponent(renderComponent);
}

void Player::Update() {

}

void Player::Move(const GameObject* gridObject, const int deltaX, const int deltaY) const
{
	Movable::Move(gridObject, deltaX, deltaY);
}

void Player::Attack(Attackable* target)
{
}

void Player::TakeDamage(int damage)
{
}
