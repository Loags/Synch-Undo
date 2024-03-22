#pragma once

#include "IModifier.h"
enum class Attributes;

class EquipmentBuff : public IModifier
{
private:
	Attributes attribute;
	int value;
	int min;
	int max;

public:
	EquipmentBuff(Attributes attribute, int _min, int _max);

	void AddValue(int& baseValue) const override;
	void GenerateValue();
	Attributes GetAttribute() const { return attribute; }
	int GetValue() const { return value; }
};

