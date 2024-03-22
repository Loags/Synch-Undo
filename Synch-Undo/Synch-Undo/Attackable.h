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
	Character* character;

	Attackable(const CharacterStats::CharacterType type);
	virtual ~Attackable() = default;
	void SetCharacter(Character* character);

	virtual void Attack(Attackable* target);
	void TakeDamage(int damage);
	virtual void Die();
	virtual void Respawn();
};

