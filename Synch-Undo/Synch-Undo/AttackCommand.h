#pragma once
#include "Command.h"

class Character;

class AttackCommand : public Command
{

private:
	Character* target;
	Character* attacker;

public:
	explicit AttackCommand(GameObject* object);
	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
	AttackCommand* Clone() const override {
		return new AttackCommand(*this);
	}
};

