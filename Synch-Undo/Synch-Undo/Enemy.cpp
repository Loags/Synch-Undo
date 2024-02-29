#include "Enemy.h"

#include "RenderComponent.h"


Enemy::Enemy(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int enemySize) :
	Character(owner, gridObject, offSet, CharacterStats::Enemy, 2, 1)
{
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, enemySize, enemySize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 255, 0, 0, 255 });
	owner->AddComponent(renderComponent);
}

void Enemy::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Enemy::Die()
{
	Character::Die();
}
