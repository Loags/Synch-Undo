#include "Player.h"
#include <iostream>
#include <SDL_events.h>

#include "Enemy.h"
#include "Grid.h"
#include "RenderComponent.h"


Player::Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet,
	const int playerSize) :
	Character(owner, gridObject, offSet, CharacterStats::Player, 5, 1, "PlayerComponent")
{
	transformComponent = new TransformComponent(owner, posX + offSet, posY + offSet, playerSize,
		playerSize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, nullptr, SDL_Color{ 0, 255, 0, 255 });
	owner->AddComponent(renderComponent);
}

void Player::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Player::Update()
{

}

