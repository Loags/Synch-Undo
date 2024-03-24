#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include "IModifier.h"

class ModifiableInt {
	int baseValue;
	int modifiedValue;
	std::vector<IModifier*> modifiers;
	std::function<void()> ValueModified;

public:
	ModifiableInt(std::function<void()> callback = nullptr);

	void SetBaseValue(int value);
	int GetBaseValue() const { return baseValue; }
	int GetModifiedValue() const { return modifiedValue; }
	void AddModifier(IModifier* modifier);
	void RemoveModifier(IModifier* modifier);
	void UpdateModifiedValue();
};
