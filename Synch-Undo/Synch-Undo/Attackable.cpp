#include "Attackable.h"

#include "AttackCommand.h"
#include "Attribute.h"
#include "Character.h"
#include "DieCommand.h"
#include "RespawnCommand.h"

Attackable::Attackable(const CharacterStats::CharacterType type) :
	commandInvoker(nullptr),
	character(nullptr)
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
	target->TakeDamage(character->GetMaxValueOfAttributeType(Attributes::AttackPower));
}

void Attackable::TakeDamage(int damage)
{
	if (character->GetIsDead()) return;

	damage -= character->GetMaxValueOfAttributeType(Attributes::Armor);
	if (damage < 0)
		damage = 0;

	int currentHealth = character->GetCurrentHealth();

	character->SetCurrentHealth(currentHealth -= damage);

	if (character->GetCurrentHealth() <= 0)
	{
		Die();
	}
}

void Attackable::Die()
{
	character->SetIsDead(true);
	DieCommand* dieCommand = new DieCommand(character->GetOwner());
	commandInvoker->ExecuteCommand(dieCommand);
}

void Attackable::Respawn()
{
	RespawnCommand* respawnCommand = new RespawnCommand(character->GetOwner());
	commandInvoker->ExecuteCommand(respawnCommand);
}