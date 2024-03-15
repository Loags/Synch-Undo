#include "Attackable.h"

#include "AttackCommand.h"
#include "Character.h"
#include "DieCommand.h"
#include "RespawnCommand.h"

Attackable::Attackable(const int health, const int attackPower, const CharacterStats::CharacterType type) :
	stats(health, attackPower, type),
	character(nullptr),
	commandInvoker(nullptr)
{
}

void Attackable::SetCharacter(Character* character)
{
	this->character = character;
	commandInvoker = character->GetCommandInvoker();
}

void Attackable::Attack(Attackable* target)
{
	AttackCommand* attackCommand = new AttackCommand(character->GetOwner());
	commandInvoker->ExecuteCommand(attackCommand);
	target->TakeDamage(stats.GetAttackPower());
}

void Attackable::TakeDamage(const int damage)
{
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
	stats.SetIsDead(true);
	DieCommand* dieCommand = new DieCommand(character->GetOwner());
	commandInvoker->ExecuteCommand(dieCommand);
	std::cout << "execute death command!";
}

void Attackable::Respawn()
{
	RespawnCommand* respawnCommand = new RespawnCommand(character->GetOwner());
	commandInvoker->ExecuteCommand(respawnCommand);
}
