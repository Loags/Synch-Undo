#include "ScorePickUp.h"

#include "Cell.h"
#include "Player.h"
#include "ScorePickUpCommand.h"
#include "ItemManager.h"

ScorePickUp::ScorePickUp(GameObject* owner, int posX, int posY, int cellSize, Cell* cellRef, const int value) :
	Item(owner, posX, posY, cellSize, cellRef),
	value(value)
{
	renderComponent = new RenderComponent(owner, itemRender, colorItem);
	owner->AddComponent(renderComponent);

	interactableType = InteractableType::ScorePickUp;
}

void ScorePickUp::Update()
{
	Item::Update();
}

void ScorePickUp::Interact()
{
	Item::Interact();

	renderComponent->SetVisible(false);
	player->SetScore(value);
	ScorePickUpCommand* scorePickUpCommand = new ScorePickUpCommand(owner, player);
	commandInvoker->ExecuteCommand(scorePickUpCommand);
	itemManager->NotifyPickUpInteracted();
}

void ScorePickUp::SpawnItem()
{
	Item::SpawnItem();
	renderComponent->SetVisible(true);
	cellRef->SetCellState(Cell::PickUp);
	SetInteracted(false);
}


