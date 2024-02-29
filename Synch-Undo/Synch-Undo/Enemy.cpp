#include "Enemy.h"

#include "RenderComponent.h"


Enemy::Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize) :
	Component(owner),
	Movable(owner, offSet),
	gridObject(gridObject)
{
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, enemySize, enemySize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 255, 0, 0, 255 });
	owner->AddComponent(renderComponent);
}

void Enemy::Update()
{
}

void Enemy::Move(const GameObject* gridObject, const int deltaX, const int deltaY) const
{
	Movable::Move(gridObject, deltaX, deltaY);
}
