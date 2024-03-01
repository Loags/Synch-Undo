#include "Cell.h"


Cell::Cell(GameObject* owner, const int posX, const int posY, const int cellSize) :
	Component("CellComponent", owner),
	characterObjectRef(nullptr)
{
	transformComponent = new TransformComponent(owner, posX, posY, cellSize, cellSize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, cellRender, colorEmpty);
	owner->AddComponent(renderComponent);
}

void Cell::Update()
{
}

