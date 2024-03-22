#include "Equipment.h"

Equipment::Equipment(std::string name, EquipmentSlot slot,
	const std::vector<std::shared_ptr<EquipmentBuff>>& equipmentBuffs) :
	name(std::move(name)),
	slot(slot),
	equipmentBuffs(equipmentBuffs)
{}
