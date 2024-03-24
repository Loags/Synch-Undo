#include "Item.h"

#include "Cell.h"
#include "GameObject.h"
#include "Player.h"

Item::Item(GameObject* owner, const int posX, const int posY, const int cellSize, Cell* cellRef) :
	Component("Item", owner),
	interacted(false),
	renderComponent(nullptr),
	cellRef(cellRef),
	player(nullptr),
	commandInvoker(nullptr)
{
	transformComponent = new TransformComponent(owner, posX, posY, cellSize, cellSize);
	owner->AddComponent(transformComponent);

	commandInvoker = owner->GetRootObject()->GetComponent<CommandInvoker>();
}

void Item::Update()
{
	const GameObject* objectRef = cellRef->GetCharacterObjectRef();
	if (objectRef)
	{
		player = objectRef->GetComponent<Player>();
		if (player)
		{
			if (!GetInteracted() && renderComponent->GetVisible())
				Interact();
		}
	}

}

void Item::Interact()
{
	SetInteracted(true);
}

void Item::SpawnItem()
{
}
