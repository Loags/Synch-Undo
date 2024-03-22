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
	target->SetCurrentHealth(target->GetCurrentHealth() + attacker->GetMaxValueOfAttributeType(Attributes::AttackPower));
}

std::string AttackCommand::ToString() const
{
	const std::string& damageDealer = CharacterStats::CharacterTypeStrings[attacker->type];
	const std::string& damageReceiver = CharacterStats::CharacterTypeStrings[target->type];

	std::string output = "AttackCommand: " + damageDealer + " damage dealt " + std::to_string(attacker->GetMaxValueOfAttributeType(Attributes::AttackPower)) +
		"  |  " + damageReceiver + " health lost: " + std::to_string(attacker->GetMaxValueOfAttributeType(Attributes::AttackPower));
	return output;
}
