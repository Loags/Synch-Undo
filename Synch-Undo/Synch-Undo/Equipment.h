#pragma once
#include <vector>
#include <memory>
#include <string>

#include "EquipmentBuff.h"

enum class EquipmentSlot {
	Helmet,
	Chestplate,
	Gloves,
	Legs,
	Boots,
	Weapon,
	TOTAL_SLOTS
};

class Equipment {
public:
	std::string name;
	EquipmentSlot slot;
	std::vector<std::shared_ptr<EquipmentBuff>> equipmentBuffs;

	Equipment(std::string name, EquipmentSlot slot, const std::vector<std::shared_ptr<EquipmentBuff>>& equipmentBuffs);

};
