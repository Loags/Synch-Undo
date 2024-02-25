#include "Cell.h"

#include "GameObject.h"
#include "TransformComponent.h"

Cell::Cell(GameObject* owner) :
	Component(owner)
{}

void Cell::Update()
{
}

void Cell::Render(SDL_Renderer* renderer)
{
	const TransformComponent* transform = owner->GetComponent<TransformComponent>();
	const SDL_Rect cellRect = { transform->GetX(),transform->GetY(), transform->GetWidth(),transform->GetHeight() };

	switch (cellState)
	{
	case Empty:
		SDL_SetRenderDrawColor(renderer, colorEmpty.r, colorEmpty.g, colorEmpty.b, colorEmpty.a);
		break;
	case Occupied:
		SDL_SetRenderDrawColor(renderer, colorOccupied.r, colorOccupied.g, colorOccupied.b, colorOccupied.a);
		break;
	case Wall:
		SDL_SetRenderDrawColor(renderer, colorWall.r, colorWall.g, colorWall.b, colorWall.a);
		break;
	}

	SDL_RenderFillRect(renderer, &cellRect);
}


