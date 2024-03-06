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

	keyMap = {
			{SDLK_w, Direction::North},
			{SDLK_s, Direction::South},
			{SDLK_a, Direction::West},
			{SDLK_d, Direction::East}
	};
	attackKey = SDLK_SPACE;
}

void Player::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Player::Die()
{
	Character::Die();
}

void Player::Respawn()
{
	Character::Respawn();
}

void Player::Update()
{
	Character::Update();
}

