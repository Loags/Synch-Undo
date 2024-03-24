#pragma once
#include <map>
#include "Equipment.h"

class Character;

class EquipmentManager {
	std::map<EquipmentSlot, std::shared_ptr<Equipment>> equippedItems;
	Character* character;

public:
	EquipmentManager();

	void SetCharacter(Character* characterRef);
	void EquipItem(const std::shared_ptr<Equipment>& item);
	void UnequipItem(const EquipmentSlot slot);

	static std::string EquipmentSlotToString(const EquipmentSlot slot);
	static std::string AttributesToString(const Attributes attribute);
	void DisplayEquippedItems() const;
	int CountEquippedItems() const { return equippedItems.size(); }
    std::vector<EquipmentSlot> GetEmptySlots() const;
	void UnequipAllItems();
	bool UnequipItemBySlot(const std::string& slotName);
};
