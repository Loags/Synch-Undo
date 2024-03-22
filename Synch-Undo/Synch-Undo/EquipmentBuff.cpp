#include "EquipmentBuff.h"

#include <iostream>
#include <random>

EquipmentBuff::EquipmentBuff(Attributes attribute, int _min, int _max) :
	attribute(attribute),
	min(_min),
	max(_max)
{
	GenerateValue();
}

void EquipmentBuff::AddValue(int& baseValue) const
{
	baseValue += value;
}

void EquipmentBuff::GenerateValue()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
	value = dist6(rng);
}
