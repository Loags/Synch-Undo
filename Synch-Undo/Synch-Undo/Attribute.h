#pragma once

#include "ModifiableInt.h"

class CharacterStats;

enum class Attributes {
	Health,
	AttackPower,
	Armor
};


class Attribute {
private:
	CharacterStats* parent;
	Attributes type;
	ModifiableInt value;

public:
	Attribute(Attributes type, int baseValue, CharacterStats* parent);

	void SetParent(CharacterStats* parent) { this->parent = parent; }

	ModifiableInt GetValue() const { return value; }
	Attributes GetType() const { return type; }
};

