#pragma once
#include "CharacterStats.h"

class GameObject;

class Attackable
{
public:
	CharacterStats stats;

	Attackable(const int health, const int attackPower, const CharacterStats::CharacterType type);
	virtual ~Attackable() = default;

	virtual void Attack(Attackable* target);
	void TakeDamage(const int damage);
	virtual void Die();
	virtual void Respawn();

	bool IsAlive() const { return stats.GetHealth() > 0; }
};

