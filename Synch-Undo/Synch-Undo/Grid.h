#pragma once
#include "Component.h"
#include <vector>
#include "Cell.h"
#include "CharacterStats.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class GameObject;

class Grid : public Component {

private:
	int rows;
	int cols;
	int cellSize;
	std::vector<std::vector<GameObject*>> cellObjects;

	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> gridLineRender = [this](SDL_Renderer* renderer, const TransformComponent* transform, const SDL_Color color) {
		for (int row = 0; row <= rows; ++row) {
			SDL_RenderDrawLine(renderer, 0, row * cellSize, cols * cellSize, row * cellSize);
		}
		for (int col = 0; col <= cols; ++col) {
			SDL_RenderDrawLine(renderer, col * cellSize, 0, col * cellSize, rows * cellSize);
		}
		};

	struct PathNode {
		std::pair<int, int> position;
		PathNode* parent;

		PathNode(std::pair<int, int> pos, PathNode* pParent = nullptr) :
			position(pos), parent(pParent)
		{}
	};


public:
	Grid(GameObject* owner, const int windowWidth, const int windowHeight, const int cellSize);

	void Update() override;
	int GetCellSize() const { return cellSize; }
	Cell* GetCellAtPos(const int col, const int row) const;
	bool GetIsCellEmpty(const int col, const int row) const;
	std::pair<int, int> GetPositionToGridCoords(const int posX, const int posY) const;

	void SetCellState(const int col, const int row, const Cell::CellState newState) const;
	Cell* FindDistantEmptyCell() const;
	std::pair<int, int> GetCharacterGridPosition(const CharacterStats::CharacterType characterType) const;
	std::vector<Movable::Direction> FindPathBFS(std::pair<int, int> start, std::pair<int, int> goal) const;
	bool IsCellTraversable(std::pair<int, int> pos) const;
	void CreateWallPatterns() const;
};
