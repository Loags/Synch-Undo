#pragma once
#include <string>
#include <array>

class CharacterStats
{
public:
	enum CharacterType
	{
		Player,
		Enemy
	};
	static const std::array<std::string, 2> CharacterTypeStrings;

	int health;
	int attackPower;
	CharacterType type;

	CharacterStats(const int health, const int attackPower, const CharacterType type);
};

