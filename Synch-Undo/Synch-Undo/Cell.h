#pragma once
#include <SDL_pixels.h>

#include "Component.h"

class Cell : public Component
{
public:
	enum CellState { Empty, Occupied, Wall };

private:
	CellState cellState = Empty;
	SDL_Color colorEmpty = { 128,128,128,1 };
	SDL_Color colorOccupied = { 0,128,128,1 };
	SDL_Color colorWall = { 139, 69, 19, 255 };

public:
	Cell(GameObject* owner);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	std::string GetName() const override { return "Cell"; }
	CellState GetCellState() const { return cellState; }

	void SetCellState(const CellState newCellState) { cellState = newCellState; }
};

