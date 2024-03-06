#include "AttackCommand.h"

AttackCommand::AttackCommand(Character* character) :
	Command(character),
	target(nullptr)
{
}

void AttackCommand::Execute()
{
	target = character->GetLastAttackTarget();
}

void AttackCommand::Undo()
{
	target->stats.SetHealth(target->stats.GetHealth() + character->stats.GetAttackPower());
}

std::string AttackCommand::ToString() const
{
	const std::string& damageDealer = CharacterStats::CharacterTypeStrings[character->stats.type];
	const std::string& damageReceiver = CharacterStats::CharacterTypeStrings[target->stats.type];

	std::string output = "AttackCommand: " + damageDealer + " damage dealt " + std::to_string(character->stats.GetAttackPower()) +
		"  |  " + damageReceiver + " health lost: " + std::to_string(character->stats.GetAttackPower());
	return output;
}
