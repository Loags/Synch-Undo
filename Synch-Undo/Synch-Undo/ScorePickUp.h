#pragma once
#include "Item.h"

class ScorePickUp final : public Item
{
private:
	SDL_Color colorItem = { 0, 0, 255, 255 };
	int value;

	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> itemRender = [this]
	(SDL_Renderer* renderer, const TransformComponent* transform, const SDL_Color color)
		{
			const SDL_Rect cellRect = { transform->GetX(),transform->GetY(), transform->GetWidth(),transform->GetHeight() };
			SDL_SetRenderDrawColor(renderer, colorItem.r, colorItem.g, colorItem.b, colorItem.a);
			SDL_RenderFillRect(renderer, &cellRect);
		};


public:
	ScorePickUp(GameObject* owner, int posX, int posY, int cellSize, Cell* cellRef, const int value);
	~ScorePickUp() override = default;
	void Update() override;
	void Interact() override;
	void SpawnItem() override;
	int GetValue() const override { return value; }
	void SetValue(int amount) { value = amount; }
};

