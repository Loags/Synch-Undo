#include "ModifiableInt.h"

#include <iostream>

ModifiableInt::ModifiableInt(std::function<void()> callback) :
	baseValue(0),
	modifiedValue(0),
	ValueModified(callback)
{
	UpdateModifiedValue();
}

void ModifiableInt::SetBaseValue(int value)
{
	baseValue = value;
	UpdateModifiedValue();
}

void ModifiableInt::AddModifier(IModifier* modifier)
{
	modifiers.push_back(modifier);
	UpdateModifiedValue();
}

void ModifiableInt::RemoveModifier(IModifier* modifier)
{
	modifiers.erase(std::remove(modifiers.begin(), modifiers.end(), modifier), modifiers.end());
	UpdateModifiedValue();
}

void ModifiableInt::UpdateModifiedValue()
{
	int valueToAdd = 0;
	for (const IModifier* modifier : modifiers) {
		modifier->AddValue(valueToAdd);
	}
	modifiedValue = baseValue + valueToAdd;
	std::cout << "ModifiedValue: " << modifiedValue << " with base: " << baseValue << " for instance: " << this << "\n";
	if (ValueModified) ValueModified();
}
