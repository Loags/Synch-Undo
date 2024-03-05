#include "CommandInvoker.h"

#include <iostream>
#include "Command.h"


CommandInvoker::CommandInvoker(GameObject* owner) :
	Component("CommandInvoker", owner)
{
}

void CommandInvoker::ExecuteCommand(Command* command)
{
	const bool success = command->Execute();
	if (success) {
		commandStack.push(std::unique_ptr<Command>(command));
		DebugCommandStack();
	}
	else {
		delete command;
	}
}

void CommandInvoker::Undo()
{
	if (!commandStack.empty()) {
		const std::unique_ptr<Command>& command = commandStack.top();
		command->Undo();
		commandStack.pop();
		DebugCommandStack();
	}
}

void CommandInvoker::Update()
{
}

void CommandInvoker::DebugCommandStack()
{
	std::stack<std::unique_ptr<Command>> tempStack;

	std::cout << "Current Command Stack:" << "\n";
	while (!commandStack.empty()) {

		std::cout << "  - " << commandStack.top()->ToString() << "\n";

		tempStack.push(std::move(commandStack.top()));
		commandStack.pop();
	}

	while (!tempStack.empty()) {
		commandStack.push(std::move(tempStack.top()));
		tempStack.pop();
	}

	std::cout << "\n\n\n\n";
}
