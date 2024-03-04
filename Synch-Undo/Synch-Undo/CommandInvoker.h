#pragma once
#include <memory>
#include <stack>

#include "Command.h"
#include "Component.h"

class CommandInvoker : public Component
{
private:
	std::stack<std::unique_ptr<Command>> commandStack;

public:
	CommandInvoker(GameObject* owner);

	void ExecuteCommand(Command* command);
	void Undo();
	void Update() override;
	void DebugCommandStack();
};

