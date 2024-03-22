#pragma once
#include <memory>

#include "Equipment.h"

class Equipment;

class EquipmentFactory {
public:
    static std::shared_ptr<Equipment> CreateHelmet();
    static std::shared_ptr<Equipment> CreateChest();
    static std::shared_ptr<Equipment> CreateGloves();
    static std::shared_ptr<Equipment> CreateLegs();
    static std::shared_ptr<Equipment> CreateBoots();
    static std::shared_ptr<Equipment> CreateWeapon();

    static std::shared_ptr<Equipment> CreateRandomEquipment();
    static std::shared_ptr<Equipment> CreateRandomEquipmentForEmptySlots(const std::vector<EquipmentSlot>& emptySlots);
};
