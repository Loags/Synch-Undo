#pragma once
#include <SDL_pixels.h>

#include "Component.h"
#include "RenderComponent.h"
#include "GameObject.h"


class Cell : public Component
{
public:
	enum CellState { Empty, Occupied, Wall, PickUp };

private:
	CellState cellState = Empty;
	SDL_Color colorEmpty = { 128,128,128,255 };
	SDL_Color colorOccupied = { 0,128,128,255 };
	SDL_Color colorWall = { 139, 69, 19, 255 };
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	const GameObject* characterObjectRef;

	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> cellRender = [this](SDL_Renderer* renderer, const TransformComponent* transform, const SDL_Color color) {
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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &cellRect);
		};

public:
	Cell(GameObject* owner, const int posX, const int posY, const int cellSize);
	void Update() override;

	CellState GetCellState() const { return cellState; }
	const GameObject* GetCharacterObjectRef() const { return characterObjectRef; }
	std::pair<int, int> GetCellPos() const { return { transformComponent->GetX(), transformComponent->GetY() }; }

	void SetCellState(const CellState newCellState) { cellState = newCellState; }
	void SetCharacterObjectRef(const GameObject* newCharacterObjectRef) { characterObjectRef = newCharacterObjectRef; }
};

