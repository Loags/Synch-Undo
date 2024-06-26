#include "EquipmentManager.h"

#include <iomanip>
#include <set>

#include "Character.h"

EquipmentManager::EquipmentManager() :
	character(nullptr)
{}

void EquipmentManager::SetCharacter(Character* characterRef)
{
	this->character = characterRef;
}

void EquipmentManager::EquipItem(const std::shared_ptr<Equipment>& item)
{
	const std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<
		const EquipmentSlot, std::shared_ptr<Equipment>>>>> current = equippedItems.find(item->slot);
	if (current != equippedItems.end()) {
		UnequipItem(item->slot);
	}

	equippedItems[item->slot] = item;

	for (const std::shared_ptr<EquipmentBuff>& equipmentBuff : item->equipmentBuffs) {
		character->AddModifierToAttribute(equipmentBuff->GetAttribute(), equipmentBuff.get());
	}
}

void EquipmentManager::UnequipItem(const EquipmentSlot slot)
{
	const std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<
		const EquipmentSlot, std::shared_ptr<Equipment>>>>> it = equippedItems.find(slot);
	if (it != equippedItems.end()) {
		for (const std::shared_ptr<EquipmentBuff>& equipmentBuff : it->second->equipmentBuffs) {
			character->RemoveModifierFromAttribute(equipmentBuff->GetAttribute(), equipmentBuff.get());
		}
		equippedItems.erase(it);
	}
}

std::string EquipmentManager::EquipmentSlotToString(const EquipmentSlot slot)
{
	switch (slot) {
	case EquipmentSlot::Helmet: return "Helmet";
	case EquipmentSlot::Chestplate: return "Chestplate";
	case EquipmentSlot::Gloves: return "Gloves";
	case EquipmentSlot::Legs: return "Legs";
	case EquipmentSlot::Boots: return "Boots";
	case EquipmentSlot::Weapon: return "Weapon";
	default: return "Unknown";
	}
}

std::string EquipmentManager::AttributesToString(const Attributes attribute)
{
	switch (attribute) {
	case Attributes::Health: return "Health";
	case Attributes::AttackPower: return "Attack Power";
	case Attributes::Armor: return "Armor";
	default: return "Unknown";
	}
}

void EquipmentManager::DisplayEquippedItems() const {
	std::cout << "================ Equipped Items =================\n\n";
	if (equippedItems.empty()) {
		std::cout << "No items equipped.\n";
	}
	else {
		std::map<Attributes, int> totalStats;

		for (const std::pair<const EquipmentSlot, std::shared_ptr<Equipment>>& itemPair : equippedItems) {
			const EquipmentSlot& slot = itemPair.first;
			const std::shared_ptr<Equipment>& item = itemPair.second;

			std::cout << EquipmentSlotToString(slot) << ":\n";

			for (const std::shared_ptr<EquipmentBuff>& buff : item->equipmentBuffs) {
				std::cout << std::setw(6) << " " << AttributesToString(buff->GetAttribute())
					<< ": +" << buff->GetValue() << "\n";

				totalStats[buff->GetAttribute()] += buff->GetValue();
			}
			std::cout << "\n";
		}

		std::cout << "Combined Stats from Equipment:\n";
		for (const std::pair<const Attributes, int>& stat : totalStats) {
			std::cout << std::setw(6) << " " << AttributesToString(stat.first) << ": +" << stat.second << "\n";
		}
	}
}

std::vector<EquipmentSlot> EquipmentManager::GetEmptySlots() const
{
	std::vector<EquipmentSlot> emptySlots;
	std::set<EquipmentSlot> occupiedSlots;

	for (const std::pair<const EquipmentSlot, std::shared_ptr<Equipment>>& item : equippedItems) {
		occupiedSlots.insert(item.first);
	}

	for (int slot = static_cast<int>(EquipmentSlot::Helmet); slot != static_cast<int>(EquipmentSlot::TOTAL_SLOTS); ++slot) {
		if (occupiedSlots.find(static_cast<EquipmentSlot>(slot)) == occupiedSlots.end()) {
			emptySlots.push_back(static_cast<EquipmentSlot>(slot));
		}
	}

	return emptySlots;
}

void EquipmentManager::UnequipAllItems() {
	for (auto it = equippedItems.begin(); it != equippedItems.end(); ) {
		UnequipItem(it->first);
		it = equippedItems.begin();
	}
}

bool EquipmentManager::UnequipItemBySlot(const std::string& slotName) {
	EquipmentSlot slot;
	if (slotName == "helmet") slot = EquipmentSlot::Helmet;
	else if (slotName == "chestplate") slot = EquipmentSlot::Chestplate;
	else if (slotName == "gloves") slot = EquipmentSlot::Gloves;
	else if (slotName == "legs") slot = EquipmentSlot::Legs;
	else if (slotName == "boots") slot = EquipmentSlot::Boots;
	else if (slotName == "weapon") slot = EquipmentSlot::Weapon;
	else return false;

	if (equippedItems.find(slot) != equippedItems.end()) {
		UnequipItem(slot);
		return true;
	}
	return false;
}
