#include "CharacterStats.h"

#include <iostream>


CharacterStats::CharacterStats(const int baseHealthValue, const int baseAttackPowerValue, const CharacterType type) :
	isDead(false),
	currentHealth(baseHealthValue),
	type(type)
{
	attributes.push_back(Attribute(Attributes::Health, baseHealthValue, this));
	attributes.push_back(Attribute(Attributes::AttackPower, baseAttackPowerValue, this));
	attributes.push_back(Attribute(Attributes::Armor, 0, this));
}

const std::array<std::string, 2> CharacterStats::CharacterTypeStrings = { "Player", "Enemy" };

int CharacterStats::GetIndexOfAttributeInList(const Attributes type) const
{
	for (size_t i = 0; i < attributes.size(); i++)
		if (type == attributes[i].GetType())
			return i;

	return -1;
}

int CharacterStats::GetBaseValueOfAttributeType(const Attributes type) const
{
	const int index = GetIndexOfAttributeInList(type);

	if (index < 0) return -1;

	return attributes[index].GetValue().GetBaseValue();
}

int CharacterStats::GetMaxValueOfAttributeType(const Attributes type) const
{
	const int index = GetIndexOfAttributeInList(type);

	if (index < 0) return -1;
	return attributes[index].GetValue().GetModifiedValue();
}

void CharacterStats::AddModifierToAttribute(const Attributes type, IModifier* modifier) const
{
	for (const Attribute& attribute : attributes) {
		if (attribute.GetType() == type) {
			attribute.GetValue().AddModifier(modifier);
			break;
		}
	}
}

void CharacterStats::RemoveModifierFromAttribute(const Attributes type, IModifier* modifier) const
{
	for (const Attribute& attribute : attributes) {
		if (attribute.GetType() == type) {
			attribute.GetValue().RemoveModifier(modifier);
			break;
		}
	}
}

void CharacterStats::SetCurrentHealth(int newCurrentHealth)
{
	currentHealth = newCurrentHealth;
	if (currentHealth < 0)
		currentHealth = 0;

	if (currentHealth > GetMaxValueOfAttributeType(Attributes::Health))
		currentHealth = GetMaxValueOfAttributeType(Attributes::Health);
}

void CharacterStats::AttributeModified() const
{
	//DebugLogAttributes();
}

void CharacterStats::DebugLogAttributes() const
{
	/*std::cout << "Health: " << GetMaxValueOfAttributeType(Attributes::Health) << "\n";
	std::cout << "AttackPower: " << GetMaxValueOfAttributeType(Attributes::AttackPower) << "\n";
	std::cout << "Armor: " << GetMaxValueOfAttributeType(Attributes::Armor) << "\n";*/
}

