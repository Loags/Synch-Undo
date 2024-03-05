#pragma once
#include "Command.h"

class AttackCommand : public Command
{

private:
	Character* target;

public:
	explicit AttackCommand(Character* character);
	bool Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

