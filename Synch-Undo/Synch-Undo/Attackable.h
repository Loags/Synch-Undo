#pragma once
#include "CharacterStats.h"
#include "CommandInvoker.h"

class Character;
class GameObject;

class Attackable
{
private:
	CommandInvoker* commandInvoker;

public:
	CharacterStats stats;
	Character* character;

	Attackable(const int health, const int attackPower, const CharacterStats::CharacterType type);
	virtual ~Attackable() = default;
	void SetCharacter(Character* character);

	virtual void Attack(Attackable* target);
	void TakeDamage(const int damage);
	virtual void Die();
	virtual void Respawn();

	bool IsAlive() const { return stats.GetHealth() > 0; }
};

