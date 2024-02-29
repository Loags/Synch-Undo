#include "Attackable.h"

#include <iostream>


Attackable::Attackable(const int health, const int attackPower, const CharacterStats::CharacterType type) :
	stats(health, attackPower, type)
{
}

void Attackable::Attack(Attackable* target)
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " attacking " << CharacterStats::CharacterTypeStrings[target->stats.type] << "\n";
	target->TakeDamage(stats.attackPower);
}

void Attackable::TakeDamage(const int damage)
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " taking " << damage << " damage" << "\n";
	stats.health -= damage;
	if (stats.health <= 0)
	{
		stats.health = 0;
		Die();
	}
}

void Attackable::Die()
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " died" << "\n";
	
}
