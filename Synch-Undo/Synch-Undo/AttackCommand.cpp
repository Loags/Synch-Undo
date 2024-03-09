#include "AttackCommand.h"

#include "Character.h"
#include "GameObject.h"

AttackCommand::AttackCommand(GameObject* object) :
	Command(object),
	target(nullptr),
	attacker(nullptr)
{
}

void AttackCommand::Execute()
{
	target = object->GetComponent<Character>()->GetLastAttackTarget();
	attacker = object->GetComponent<Character>();
}

void AttackCommand::Undo()
{
	target->stats.SetHealth(target->stats.GetHealth() + attacker->stats.GetAttackPower());
}

std::string AttackCommand::ToString() const
{
	const std::string& damageDealer = CharacterStats::CharacterTypeStrings[attacker->stats.type];
	const std::string& damageReceiver = CharacterStats::CharacterTypeStrings[target->stats.type];

	std::string output = "AttackCommand: " + damageDealer + " damage dealt " + std::to_string(attacker->stats.GetAttackPower()) +
		"  |  " + damageReceiver + " health lost: " + std::to_string(attacker->stats.GetAttackPower());
	return output;
}
