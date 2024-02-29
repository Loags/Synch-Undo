#include "CharacterStats.h"

CharacterStats::CharacterStats(const int health, const int attackPower, const CharacterType type) :
	health(health),
	attackPower(attackPower),
	type(type)
{
}
const std::array<std::string, 2> CharacterStats::CharacterTypeStrings = { "Player", "Enemy" };
