#include "Player.h"
#include <iostream>
#include <SDL_events.h>

#include "Enemy.h"
#include "Grid.h"
#include "ItemManager.h"
#include "RenderComponent.h"


Player::Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet,
	const int playerSize) :
	Character(owner, gridObject, offSet, CharacterStats::Player, 5, 1, "PlayerComponent"),
	score(0)

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

	targetTurnState = GameStateManager::TurnState::PlayerTurn;

	grid = gridObject->GetComponent<Grid>();
	const std::pair<int, int> pos = grid->GetPositionToGridCoords(posX, posY);
	grid->SetCellState(pos.first, pos.second, Cell::Occupied);
}

void Player::Move(const GameObject* gridObject, const Direction newFacingDirection)
{
	Character::Move(gridObject, newFacingDirection);
}

void Player::Die()
{
	if (GetScore() > 0)
	{
		const std::pair<int, int> playerGridPos = grid->GetPositionToGridCoords(transformComponent->GetX(), transformComponent->GetY());
		Cell* targetCell = grid->GetCellAtPos(playerGridPos.first, playerGridPos.second);
		SetScore(-score);
		itemManager->SpawnItemAtCell(targetCell, Interactable::InteractableType::ScorePickUp, score);
	}

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

