#pragma once
#include <string>

#include "Character.h"

class Command
{
protected:
	Character* character;

public:
	virtual ~Command() = default;
	Command(Character* character);
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual std::string ToString() const = 0;
};

