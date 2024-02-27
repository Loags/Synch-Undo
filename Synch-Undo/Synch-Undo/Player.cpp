#include "Player.h"

#include <iostream>

#include "GameObject.h"
#include "TransformComponent.h"


Player::Player(GameObject* owner, const GameObject* gridObject, const int x, const int y, const int offSet, const int playerSize)
	: Component(owner),
	gridObject(gridObject),
	x(x),
	y(y),
	offSet(offSet)
{
	colorPlayer = { 0, 255, 0, 255 };
	TransformComponent* transformComponent = new TransformComponent(owner, x + offSet, y + offSet, playerSize, playerSize);
	owner->AddComponent(transformComponent);
}

void Player::Update() {

}

void Player::Render(SDL_Renderer* renderer) {
	const TransformComponent* transform = owner->GetComponent<TransformComponent>();
	const SDL_Rect playerRect = { transform->GetX(), transform->GetY(), transform->GetWidth(), transform->GetHeight() };
	SDL_SetRenderDrawColor(renderer, colorPlayer.r, colorPlayer.g, colorPlayer.b, colorPlayer.a);
	SDL_RenderFillRect(renderer, &playerRect);
}

void Player::Move(const int deltaX, const int deltaY) const
{
	const Grid* grid = gridObject->GetComponent<Grid>();
	TransformComponent* transform = owner->GetComponent<TransformComponent>();

	const int newPosX = transform->GetX() + deltaX;
	const int newPosY = transform->GetY() + deltaY;

	const int cellSize = grid->GetCellSize();
	const int gridX = (newPosX + offSet) / cellSize;
	const int gridY = (newPosY + offSet) / cellSize;

	const Cell* targetCell = grid->GetCellAtPos(gridX, gridY);

	if (targetCell == nullptr) return;

	if (targetCell->GetCellState() == Cell::Empty) {
		transform->SetPosition(newPosX, newPosY);
	}
}
