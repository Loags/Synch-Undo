#include "ConsoleManager.h"
#include "GameObject.h"
#include <iostream>

#include "Enemy.h"
#include "PickUp.h"
#include "Player.h"
#include "Grid.h"


ConsoleManager::ConsoleManager(GameObject* owner) :
	Component("ConsoleManager", owner),
	indent(6, ' ')
{
}

void ConsoleManager::Update()
{
}

void ConsoleManager::ProcessInput()
{
	std::string input;
	const std::string printHierarchy = "hierarchy";
	const std::string printControls = "controls";
	const std::string printCommandStack = "commandstack";
	const std::string printStats = "stats";
	const std::string printPickUps = "pickups";
	const std::string printItems = "items";
	const std::string exitConsole = "exit";

	std::cout << "\n\nAvailable commands:\n";
	std::cout << indent << printHierarchy << "  -  Overview of all GameObjects and their Components!\n";
	std::cout << indent << printControls << "  -  Overview of all inputs for the Player and Enemy!\n";
	std::cout << indent << printCommandStack << "  -  Stack overview of all commands the Player and Enemy executed!\n";
	std::cout << indent << printStats << "  -  Overview of all stats for the Player and Enemy!\n";
	std::cout << indent << printPickUps << "  -  Overview of all PickUps on the Grid!\n";
	std::cout << indent << printItems << "  -  Overview of all Items on the Grid!\n";
	std::cout << indent << exitConsole << "  -  Exit the console and enable input for the game!\n\n\n";


	std::cout << "Enter command: ";
	std::getline(std::cin, input);

	if (input == printHierarchy) {
		owner->PrintComponentsAndChildren(0);
		std::cout << "\n================================================\n";
	}
	else if (input == printControls)
	{
		ShowControls();
	}
	else if (input == printCommandStack)
	{
		ShowCommandStack();
	}
	else if (input == printStats)
	{
		ShowStats();
	}
	else if (input == printPickUps)
	{
		ShowPickups();
	}
	else if (input == printItems)
	{
		ShowItems();
	}
	else if (input == exitConsole)
	{
		SetConsoleAccess(false);
	}
	else {
		std::cout << "Unknown command. Please try again.\n";
	}
}

void ConsoleManager::ShowControls() const
{
	const Player* player = owner->GetComponentInChildren<Player>();
	const Enemy* enemy = owner->GetComponentInChildren<Enemy>();
	std::cout << "\n================ Character Controls ================\n\n";
	std::cout << "\nPlayer Controls:\n";
	std::cout << "Hold SHIFT while pressing move keys to Rotate instead of moving.\n";
	for (const std::pair<const int, Movable::Direction>& keyMap : player->GetKeyMap()) {
		std::cout << indent << "Move " << DirectionToString(keyMap.second) << ": " << SDL_GetKeyName(keyMap.first) << "\n";
	}
	std::cout << indent << "Attack: " << SDL_GetKeyName(player->GetAttackKey()) << "\n\n";

	std::cout << "Enemy Controls:\n";
	std::cout << "Hold SHIFT while pressing move keys to Rotate instead of moving.\n";
	for (const std::pair<const int, Movable::Direction>& keyMap : enemy->GetKeyMap()) {
		std::cout << indent << "Move " << DirectionToString(keyMap.second) << ": " << SDL_GetKeyName(keyMap.first) << "\n";
	}
	std::cout << indent << "Attack: " << SDL_GetKeyName(enemy->GetAttackKey()) << "\n";
	std::cout << "\n================================================\n";
}

void ConsoleManager::ShowStats() const
{
	const Player* player = owner->GetComponentInChildren<Player>();
	const Enemy* enemy = owner->GetComponentInChildren<Enemy>();

	std::cout << "\n================ Character Stats ================\n\n";
	std::cout << "Player Stats:\n";
	std::cout << indent << "Health: " << player->stats.GetHealth() << " / " << player->stats.GetInitialHealth() << "\n";
	std::cout << indent << "Attack Power: " << player->stats.GetAttackPower() << "\n";
	std::cout << indent << "Status: " << (player->stats.GetIsDead() ? "Dead" : "Alive") << "\n";
	std::cout << indent << "Score: " << player->GetScore() << "\n\n";

	std::cout << "Enemy Stats:\n";
	std::cout << indent << "Health: " << enemy->stats.GetHealth() << " / " << enemy->stats.GetInitialHealth() << "\n";
	std::cout << indent << "Attack Power: " << enemy->stats.GetAttackPower() << "\n";
	std::cout << indent << "Status: " << (enemy->stats.GetIsDead() ? "Dead" : "Alive") << "\n";
	std::cout << "\n================================================\n";
}

void ConsoleManager::ShowPickups() const {
	std::cout << "\n================ Pickups ================\n\n";
	const std::vector<GameObject*> pickUpObjects = owner->GetAllGameObjectWithComponent<PickUp>();
	for (GameObject* const& pickupObject : pickUpObjects) {
		const PickUp* pickup = pickupObject->GetComponent<PickUp>();
		const Grid* grid = owner->GetComponentInChildren<Grid>();
		const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(pickup->GetCellRef()->GetCellPos().first,
			pickup->GetCellRef()->GetCellPos().second);
		std::cout << "Pickup:\n";
		std::cout << indent << "Location: " << pickup->GetOwner()->GetComponent<TransformComponent>()->GetX() << ", " <<
			pickup->GetOwner()->GetComponent<TransformComponent>()->GetY() << "\n";
		std::cout << indent << "Location Grid: " << std::to_string(gridPos.first) << ", " <<
			std::to_string(gridPos.second) << "\n";
		std::cout << indent << "Status: " << (pickup->GetIsPickedUp() ? "Collected" : "Available") << "\n";
		if (!pickup->GetIsPickedUp())
			std::cout << indent << "Value: " << pickup->GetValue() << "\n";
	}
	std::cout << "\n========================================\n";
}

void ConsoleManager::ShowItems() const
{
	std::cout << "\n================ Items ================\n\n";
	const std::vector<GameObject*> itemObjects = owner->GetAllGameObjectWithComponent<Item>();
	for (GameObject* const& itemObject : itemObjects) {
		const Item* item = itemObject->GetComponent<Item>();
		const Grid* grid = owner->GetComponentInChildren<Grid>();
		const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(item->GetCellRef()->GetCellPos().first,
			item->GetCellRef()->GetCellPos().second);
		std::cout << "Item: (" << Item::InteractableToString(item->GetInteractableType()) << ")\n";
		std::cout << indent << "Location: " << item->GetOwner()->GetComponent<TransformComponent>()->GetX() << ", " <<
			item->GetOwner()->GetComponent<TransformComponent>()->GetY() << "\n";
		std::cout << indent << "Location Grid: " << std::to_string(gridPos.first) << ", " <<
			std::to_string(gridPos.second) << "\n";

		if (item->GetInteractableType() == Interactable::InteractableType::PickUp)
		{
			const PickUp* pickUp = dynamic_cast<const PickUp*>(item);
			if (pickUp) {
				std::cout << indent << "Status: " << (pickUp->GetIsPickedUp() ? "Collected" : "Available") << "\n";
				if (!pickUp->GetIsPickedUp())
					std::cout << indent << "Value: " << pickUp->GetValue() << "\n";
			}
		}
	}
	std::cout << "\n========================================\n";
}

void ConsoleManager::ShowCommandStack() const
{
	std::cout << "\n================ Command Stack ================\n\n";
	owner->GetComponent<CommandInvoker>()->DebugCommandStack();
	std::cout << "\n========================================\n";
}
