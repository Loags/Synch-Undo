#pragma once
#include <memory>
#include <stack>
#include "Component.h"

class Command;

class CommandInvoker : public Component
{
private:
	std::stack<std::unique_ptr<Command>> commandStack;
	int counter = 0;

public:
	CommandInvoker(GameObject* owner);

	void ExecuteCommand(Command* command);
	void Undo();
	void Update() override;
	void DebugCommandStack();
};

