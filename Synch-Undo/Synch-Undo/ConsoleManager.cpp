#include "ConsoleManager.h"

#include <iomanip>

#include "GameObject.h"
#include <iostream>

#include "Enemy.h"
#include "EquipmentFactory.h"
#include "ScorePickUp.h"
#include "HealthPickUp.h"
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
	const std::string printScorePickUps = "scorepickups";
	const std::string printHealthPickUps = "healthpickups";
	const std::string printItems = "items";
	const std::string exitConsole = "exit";

	std::cout << "\n\nAvailable commands:\n";
	std::cout << indent << printHierarchy << "  -  Overview of all GameObjects and their Components!\n";
	std::cout << indent << printControls << "  -  Overview of all inputs for the Player and Enemy!\n";
	std::cout << indent << printCommandStack << "  -  Stack overview of all commands the Player and Enemy executed!\n";
	std::cout << indent << printStats << "  -  Overview of all stats for the Player and Enemy!\n";
	std::cout << indent << printScorePickUps << "  -  Overview of all ScorePickUps on the Grid!\n";
	std::cout << indent << printHealthPickUps << "  -  Overview of all HealthPickUps on the Grid!\n";
	std::cout << indent << printItems << "  -  Overview of all Items on the Grid!\n";
	std::cout << indent << "equiprandom_<p/e>_<number>" <<
		"  -  Equip <p/e> (player / enemy) <number> random items to the player or enemy. Example: equiprandom_p_3\n";
	std::cout << indent << "unequipall_<p/e>" <<
		"  -  Unequip <p/e> (player / enemy) all items from the player or enemy. Example: unequipall_p\n";
	std::cout << indent << "unequipslot_<p/e>_<slotname>" <<
		"  -  Unequip <p/e> (player / enemy) specific item from slot of the player or enemy. Example: unequipslot_p_helmet\n";
	std::cout << indent << exitConsole << "  -  Exit the console and enable input for the game!\n\n\n";

	std::cout << "Enter command: ";
	std::getline(std::cin, input);

	if (input.rfind("equiprandom_", 0) == 0) { EquipRandomXItems(input); }
	else if (input.rfind("unequipall_", 0) == 0) { UnequipAll(input); }
	else if (input.rfind("unequipslot_", 0) == 0) { UnequipSlot(input); }
	else if (input == printHierarchy) {
		owner->PrintComponentsAndChildren(0);
		std::cout << "\n================================================\n";
	}
	else if (input == printControls) { ShowControls(); }
	else if (input == printCommandStack) { ShowCommandStack(); }
	else if (input == printStats) { ShowStats(); }
	else if (input == printScorePickUps) { ShowScorePickups(); }
	else if (input == printHealthPickUps) { ShowHealthPickUps(); }
	else if (input == printItems) { ShowItems(); }
	else if (input == exitConsole) { SetConsoleAccess(false); }
	else { std::cout << "Unknown command. Please try again.\n"; }
}

void ConsoleManager::ShowControls() const
{
	const Player* player = owner->GetComponentInChildren<Player>();
	std::cout << "\n================ Character Controls ================\n\n";
	std::cout << "\nPlayer Controls:\n";
	std::cout << "Hold SHIFT while pressing move keys to Rotate instead of moving.\n";
	for (const std::pair<const int, Movable::Direction>& keyMap : player->GetKeyMap()) {
		std::cout << indent << "Move " << DirectionToString(keyMap.second) << ": " << SDL_GetKeyName(keyMap.first) << "\n";
	}
	std::cout << indent << "Attack: " << SDL_GetKeyName(player->GetAttackKey()) << "\n";
	std::cout << "\n================================================\n";
}

void ConsoleManager::ShowStats() const
{
	const Player* player = owner->GetComponentInChildren<Player>();
	const Enemy* enemy = owner->GetComponentInChildren<Enemy>();

	std::cout << "\n================ Player Stats ================\n\n";
	std::cout << "Player Stats:\n";
	std::cout << indent << "Health: " << player->GetCurrentHealth() << " / " << player->GetMaxValueOfAttributeType(Attributes::Health) << "\n";
	std::cout << indent << "Attack Power: " << player->GetMaxValueOfAttributeType(Attributes::AttackPower) << "\n";
	std::cout << indent << "Armor: " << player->GetMaxValueOfAttributeType(Attributes::Armor) << "\n";
	std::cout << indent << "Status: " << (player->GetIsDead() ? "Dead" : "Alive") << "\n";
	std::cout << indent << "Score: " << player->GetScore() << "\n\n";
	player->DisplayEquippedItems();
	std::cout << "\n================================================\n";
	std::cout << "\n================ Enemy Stats ================\n\n";
	std::cout << "Enemy Stats:\n";
	std::cout << indent << "Health: " << enemy->GetCurrentHealth() << " / " << enemy->GetMaxValueOfAttributeType(Attributes::Health) << "\n";
	std::cout << indent << "Attack Power: " << enemy->GetMaxValueOfAttributeType(Attributes::AttackPower) << "\n";
	std::cout << indent << "Armor: " << enemy->GetMaxValueOfAttributeType(Attributes::Armor) << "\n";
	std::cout << indent << "Status: " << (enemy->GetIsDead() ? "Dead" : "Alive") << "\n";
	enemy->DisplayEquippedItems();

	std::cout << "\n================================================\n";
}

void ConsoleManager::ShowScorePickups() const {
	std::cout << "\n================ Score Pickups ================\n\n";
	const std::vector<GameObject*> pickUpObjects = owner->GetAllGameObjectWithComponent<ScorePickUp>();
	for (GameObject* const& pickupObject : pickUpObjects) {
		const ScorePickUp* pickup = pickupObject->GetComponent<ScorePickUp>();

		if (pickup->GetInteracted()) continue;

		const Grid* grid = owner->GetComponentInChildren<Grid>();
		const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(pickup->GetCellRef()->GetCellPos().first,
			pickup->GetCellRef()->GetCellPos().second);
		std::cout << "Score Pickup:\n";
		std::cout << indent << "Location: " << pickup->GetOwner()->GetComponent<TransformComponent>()->GetX() << ", " <<
			pickup->GetOwner()->GetComponent<TransformComponent>()->GetY() << "\n";
		std::cout << indent << "Location Grid: " << std::to_string(gridPos.first) << ", " <<
			std::to_string(gridPos.second) << "\n";
		std::cout << indent << "Status: " << (pickup->GetInteracted() && pickup->GetOwner()->GetComponent<RenderComponent>()->GetVisible() ? "Collected" : "Available") << "\n";
		if (!pickup->GetInteracted())
			std::cout << indent << "Value: " << pickup->GetValue() << "\n";
	}
	std::cout << "\n========================================\n";
}

void ConsoleManager::ShowHealthPickUps()const
{
	std::cout << "\n================ Health Pickups ================\n\n";
	const std::vector<GameObject*> pickUpObjects = owner->GetAllGameObjectWithComponent<HealthPickUp>();
	for (GameObject* const& pickupObject : pickUpObjects) {
		const HealthPickUp* pickup = pickupObject->GetComponent<HealthPickUp>();

		if (pickup->GetInteracted()) continue;

		const Grid* grid = owner->GetComponentInChildren<Grid>();
		const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(pickup->GetCellRef()->GetCellPos().first,
			pickup->GetCellRef()->GetCellPos().second);
		std::cout << "Health PickUp:\n";
		std::cout << indent << "Location: " << pickup->GetOwner()->GetComponent<TransformComponent>()->GetX() << ", " <<
			pickup->GetOwner()->GetComponent<TransformComponent>()->GetY() << "\n";
		std::cout << indent << "Location Grid: " << std::to_string(gridPos.first) << ", " <<
			std::to_string(gridPos.second) << "\n";
		std::cout << indent << "Status: " << (pickup->GetInteracted() && pickup->GetOwner()->GetComponent<RenderComponent>()->GetVisible() ? "Collected" : "Available") << "\n";
		if (!pickup->GetInteracted())
			std::cout << indent << "Value: " << pickup->GetValue() << "\n";
	}
	std::cout << "\n========================================\n";
}

void ConsoleManager::ShowItems() const {
	std::cout << "\n================ Items ================\n\n";

	auto printItemDetails = [this](const Item* item) {
		const Grid* grid = owner->GetComponentInChildren<Grid>();
		const std::pair<int, int> gridPos = grid->GetPositionToGridCoords(item->GetCellRef()->GetCellPos().first,
			item->GetCellRef()->GetCellPos().second);
		std::cout << "Item: (" << Item::InteractableToString(item->GetInteractableType()) << ")\n"
			<< indent << "Location: " << item->GetOwner()->GetComponent<TransformComponent>()->GetX() << ", "
			<< item->GetOwner()->GetComponent<TransformComponent>()->GetY() << "\n"
			<< indent << "Location Grid: " << std::to_string(gridPos.first) << ", "
			<< std::to_string(gridPos.second) << "\n"
			<< indent << "Status: " << (item->GetInteracted() && item->GetOwner()->GetComponent<RenderComponent>()->GetVisible() ? "Collected" : "Available") << "\n"
			<< indent << "Value: " << item->GetValue() << "\n";
		};

	const std::vector<GameObject*> itemObjects = owner->GetAllGameObjectWithComponent<Item>();
	for (GameObject* const& itemObject : itemObjects) {
		const Item* item = itemObject->GetComponent<Item>();
		if (item->GetInteracted()) continue;

		printItemDetails(item);
	}

	std::cout << "\n========================================\n";
}

void ConsoleManager::ShowCommandStack() const
{
	std::cout << "\n================ Command Stack ================\n\n";
	owner->GetComponent<CommandInvoker>()->DebugCommandStack();
	std::cout << "\n========================================\n";
}

void ConsoleManager::EquipRandomXItems(const std::string& command) const
{
	const std::size_t firstUnderscore = command.find("_");
	const std::size_t lastUnderscore = command.rfind("_");

	if (firstUnderscore == std::string::npos || lastUnderscore == std::string::npos || firstUnderscore == lastUnderscore) {
		std::cout << "Invalid command format." << '\n';
		return;
	}

	const char target = command[firstUnderscore + 1];
	int numberOfItems = 0;

	try {
		numberOfItems = std::stoi(command.substr(lastUnderscore + 1));
	}
	catch (...) {
		std::cout << "Invalid number of items specified." << '\n';
		return;
	}

	if (numberOfItems <= 0) {
		std::cout << "Number of items must be greater than 0." << '\n';
		return;
	}

	Character* characterTarget = nullptr;
	if (target == 'p') {
		characterTarget = owner->GetComponentInChildren<Player>();
	}
	else if (target == 'e') {
		characterTarget = owner->GetComponentInChildren<Enemy>();
	}
	else {
		std::cout << "Invalid target. Use 'p' for player or 'e' for enemy." << '\n';
		return;
	}

	if (characterTarget) {
		const int emptySlots = static_cast<int>(EquipmentSlot::TOTAL_SLOTS) - characterTarget->CountEquippedItems();

		const int itemsToEquip = std::min(numberOfItems, emptySlots);

		if (itemsToEquip <= 0) {
			std::cout << "No empty slots to equip new items." << '\n';
			return;
		}

		for (int i = 0; i < numberOfItems; ++i) {
			std::shared_ptr<Equipment> randomEquipment = EquipmentFactory::CreateRandomEquipmentForEmptySlots(characterTarget->GetEmptySlots());
			characterTarget->EquipItem(randomEquipment);
		}
		ShowStats();
	}
}

void ConsoleManager::UnequipAll(const std::string& command) {
	const char target = command[11];
	Character* characterTarget = GetCharacterTarget(target);

	if (!characterTarget) {
		std::cout << "Invalid target. Use 'p' for player or 'e' for enemy.\n";
		return;
	}

	characterTarget->UnequipAllItems();
	std::cout << "All items have been unequipped from " << (target == 'p' ? "player" : "enemy") << ".\n";
	ShowStats();
}

void ConsoleManager::UnequipSlot(const std::string& command) {
	const size_t underscorePos = command.find('_', 12);
	if (underscorePos == std::string::npos) return;

	const char target = command[12];
	const std::string slotName = command.substr(underscorePos + 1);

	Character* characterTarget = GetCharacterTarget(target);
	if (!characterTarget) {
		std::cout << "Invalid target. Use 'p' for player or 'e' for enemy.\n";
		return;
	}

	const bool success = characterTarget->UnequipItemBySlot(slotName);
	if (success) {
		std::cout << "Item from slot " << slotName << " has been unequipped.\n";
	}
	else {
		std::cout << "Failed to unequip item from slot " << slotName << ". Slot may be empty or incorrect.\n";
	}
	ShowStats();
}

Character* ConsoleManager::GetCharacterTarget(const char target) const {
	if (target == 'p') {
		return owner->GetComponentInChildren<Player>();
	}
	else if (target == 'e') {
		return owner->GetComponentInChildren<Enemy>();
	}
	return nullptr;
}