#include "HealthPickUp.h"

#include "Cell.h"
#include "HealthPickUpCommand.h"
#include "Player.h"

HealthPickUp::HealthPickUp(GameObject* owner, int posX, int posY, int cellSize, Cell* cellRef, const int value) :
	Item(owner, posX, posY, cellSize, cellRef),
	healAmount(value)
{
	renderComponent = new RenderComponent(owner, itemRender, colorItem);
	owner->AddComponent(renderComponent);

	interactableType = InteractableType::HealthPickUp;
}

void HealthPickUp::Update()
{
	Item::Update();
}

void HealthPickUp::Interact()
{
	Item::Interact();
	const int previousHealth = player->GetCurrentHealth();
	renderComponent->SetVisible(false);
	player->SetCurrentHealth(player->GetCurrentHealth() + healAmount);

	CommandInvoker* commandInvoker = owner->GetRootObject()->GetComponent<CommandInvoker>();
	HealthPickUpCommand* healthPickUpCommand = new HealthPickUpCommand(owner, player, previousHealth);
	commandInvoker->ExecuteCommand(healthPickUpCommand);
}

void HealthPickUp::SpawnItem()
{
	Item::SpawnItem();
	renderComponent->SetVisible(true);
	cellRef->SetCellState(Cell::PickUp);
	SetInteracted(false);
}
