#pragma once
#include "Component.h"
#include "Interactable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"


class CommandInvoker;
class Player;
class Cell;

class Item : public Component, public Interactable
{
protected:
	bool interacted;
	RenderComponent* renderComponent;
	TransformComponent* transformComponent;
	Cell* cellRef;
	Player* player;
	CommandInvoker* commandInvoker;

public:
	Item(GameObject* owner, int posX, int posY, int cellSize, Cell* cellRef);
	~Item() override = default;
	void SetCellRef(Cell* newCellRef) { cellRef = newCellRef; }
	Cell* GetCellRef() const { return cellRef; }
	bool GetInteracted() const { return interacted; }
	void SetInteracted(bool newInteracted) { interacted = newInteracted; }
	void Update() override;
	void Interact() override;
	void virtual SpawnItem();
};

