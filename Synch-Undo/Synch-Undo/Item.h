#pragma once
#include <functional>
#include <SDL_render.h>
#include "Component.h"
#include "Interactable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"


class Cell;

class Item : public Component, public Interactable
{
protected:
	SDL_Color colorItem = { 0, 0, 0, 255 };
	RenderComponent* renderComponent;
	TransformComponent* transformComponent;
	Cell* cellRef;
	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> itemRender = [this]
	(SDL_Renderer* renderer, const TransformComponent* transform, const SDL_Color color)
		{
			const SDL_Rect cellRect = { transform->GetX(),transform->GetY(), transform->GetWidth(),transform->GetHeight() };
			SDL_SetRenderDrawColor(renderer, colorItem.r, colorItem.g, colorItem.b, colorItem.a);
			SDL_RenderFillRect(renderer, &cellRect);

		};

public:
	Item(GameObject* owner, int posX, int posY, int cellSize, Cell* cellRef);
	void SetCellRef(Cell* newCellRef) { cellRef = newCellRef; }
	Cell* GetCellRef() const { return cellRef; }
	void Update() override;
	void Interact() override;
	void virtual SpawnItem();
};

