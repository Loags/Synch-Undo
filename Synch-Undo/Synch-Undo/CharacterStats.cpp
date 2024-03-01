#include "CharacterStats.h"

CharacterStats::CharacterStats(const int health, const int attackPower, const CharacterType type) :
	health(health),
	initialHealth(health),
	attackPower(attackPower),
	isDead(false),
	type(type)
{
}
const std::array<std::string, 2> CharacterStats::CharacterTypeStrings = { "Player", "Enemy" };
