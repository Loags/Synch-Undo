#include "EquipmentFactory.h"

#include <random>
#include <vector>

#include "Attribute.h"
#include "Equipment.h"

class EquipmentBuff;

std::shared_ptr<Equipment> EquipmentFactory::CreateHelmet()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::Armor, 2,4),
		std::make_shared<EquipmentBuff>(Attributes::Health, 2,5)
	};
	return std::make_shared<Equipment>("Helmet", EquipmentSlot::Helmet, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateChest()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::Health, 10,20),
		std::make_shared<EquipmentBuff>(Attributes::Armor, 1,2)
	};
	return std::make_shared<Equipment>("Chestplate", EquipmentSlot::Chestplate, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateGloves()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::AttackPower, 3,5),
		std::make_shared<EquipmentBuff>(Attributes::Armor, 1,2)
	};
	return std::make_shared<Equipment>("Gloves", EquipmentSlot::Gloves, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateLegs()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::Armor, 3,5),
		std::make_shared<EquipmentBuff>(Attributes::Health, 1,3)
	};
	return std::make_shared<Equipment>("Leg Armor", EquipmentSlot::Legs, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateBoots()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::Armor, 1,2),
		std::make_shared<EquipmentBuff>(Attributes::Health, 3,6)
	};
	return std::make_shared<Equipment>("Boots", EquipmentSlot::Boots, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateWeapon()
{
	std::vector<std::shared_ptr<EquipmentBuff>> buffs = {
		std::make_shared<EquipmentBuff>(Attributes::AttackPower, 3,6),
		std::make_shared<EquipmentBuff>(Attributes::Health, 2,4)
	};
	return std::make_shared<Equipment>("Sword", EquipmentSlot::Weapon, buffs);
}

std::shared_ptr<Equipment> EquipmentFactory::CreateRandomEquipment()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
	const int randomChoice = dist6(rng);

	switch (randomChoice) {
	case 1: return CreateHelmet();
	case 2:	return CreateChest();
	case 3:	return CreateGloves();
	case 4:	return CreateLegs();
	case 5:	return CreateBoots();
	case 6:	return CreateWeapon();
	default: throw std::runtime_error("Unexpected equipment type.");
	}
}

std::shared_ptr<Equipment> EquipmentFactory::CreateRandomEquipmentForEmptySlots(const std::vector<EquipmentSlot>& emptySlots) {
	if (emptySlots.empty()) {
		throw std::runtime_error("No empty slots available.");
	}

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, emptySlots.size() - 1);
	const EquipmentSlot randomSlot = emptySlots[dist(rng)];

	switch (randomSlot) {
	case EquipmentSlot::Helmet:
		return CreateHelmet();
	case EquipmentSlot::Chestplate:
		return CreateChest();
	case EquipmentSlot::Gloves:
		return CreateGloves();
	case EquipmentSlot::Legs:
		return CreateLegs();
	case EquipmentSlot::Boots:
		return CreateBoots();
	case EquipmentSlot::Weapon:
		return CreateWeapon();
	default:
		throw std::runtime_error("Unexpected slot type.");
	}
}
