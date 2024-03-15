#include "PickUp.h"

#include "Cell.h"
#include "PickUpCommand.h"
#include "Player.h"


class ItemManager;

PickUp::PickUp(GameObject* owner, int posX, int posY, int cellSize, ItemManager* itemManager, Cell* cellRef) :
	Item(owner, posX, posY, cellSize, cellRef),
	itemManager(itemManager),
	isPickedUp(false),
	commandInvoker(nullptr),
	value(1),
	player(nullptr)
{
	interactableType = InteractableType::PickUp;
}

void PickUp::Update()
{
	Item::Update();
	const GameObject* objectRef = cellRef->GetCharacterObjectRef();
	if (objectRef)
	{
		player = objectRef->GetComponent<Player>();
		if (player)
		{
			if (!GetIsPickedUp())
				Interact();
		}
	}
}

void PickUp::Interact()
{
	Item::Interact();
	renderComponent->SetVisible(false);
	SetIsPickedUp(true);
	player->SetScore(value);
	PickUpCommand* pickUpCommand = new PickUpCommand(owner, player);
	commandInvoker = owner->GetRootObject()->GetComponent<CommandInvoker>();
	commandInvoker->ExecuteCommand(pickUpCommand);
	itemManager->NotifyPickUpInteracted();
}

void PickUp::SpawnItem()
{
	Item::SpawnItem();
	renderComponent->SetVisible(true);
	cellRef->SetCellState(Cell::PickUp);
	SetIsPickedUp(false);
}
