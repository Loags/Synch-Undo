#include "Attackable.h"

#include <iostream>


Attackable::Attackable(const int health, const int attackPower, const CharacterStats::CharacterType type) :
	stats(health, attackPower, type)
{
}

void Attackable::Attack(Attackable* target)
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " attacking " << CharacterStats::CharacterTypeStrings[target->stats.type] << "\n";
	target->TakeDamage(stats.GetAttackPower());
}

void Attackable::TakeDamage(const int damage)
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " taking " << damage << " damage" << "\n";
	int currentHealth = stats.GetHealth();
	stats.SetHealth(currentHealth -= damage);

	if (stats.GetHealth() <= 0)
	{
		stats.SetHealth(0);
		Die();
	}
}

void Attackable::Die()
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " died" << "\n";
	stats.SetisDead(true);
}

void Attackable::Respawn()
{
	std::cout << CharacterStats::CharacterTypeStrings[stats.type] << " respawned" << "\n";
}
