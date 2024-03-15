#include "Item.h"

#include "Cell.h"
#include "GameObject.h"

Item::Item(GameObject* owner, const int posX, const int posY, const int cellSize, Cell* cellRef) :
	Component("Item", owner),
	cellRef(cellRef)
{
	transformComponent = new TransformComponent(owner, posX, posY, cellSize, cellSize);
	owner->AddComponent(transformComponent);

	renderComponent = new RenderComponent(owner, itemRender, colorItem);
	owner->AddComponent(renderComponent);
}

void Item::Update()
{
}

void Item::Interact()
{
}

void Item::SpawnItem()
{
}
