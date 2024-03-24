#pragma once
#include <string>
#include <array>

#include "Attribute.h"
#include "ModifiableInt.h"



class CharacterStats
{
private:
	std::vector<Attribute> attributes;
	bool isDead;
	int currentHealth;

public:
	enum CharacterType
	{
		Player,
		Enemy
	};
	static const std::array<std::string, 2> CharacterTypeStrings;
	CharacterType type;

	CharacterStats(const int baseHealthValue, const int baseAttackPowerValue, const CharacterType type);

	void SetIsDead(bool newDead) { isDead = newDead; }
	bool GetIsDead() const { return isDead; }

	int GetIndexOfAttributeInList(const Attributes type) const;
	int GetBaseValueOfAttributeType(const Attributes type) const;
	int GetMaxValueOfAttributeType(const Attributes type) const;
	void AddModifierToAttribute(const Attributes type, IModifier* modifier) const;
	void RemoveModifierFromAttribute(Attributes type, IModifier* modifier) const;

	int GetCurrentHealth() const { return currentHealth; }
	void SetCurrentHealth(int newCurrentHealth);
	void AttributeModified() const;
	void DebugLogAttributes() const;
};
