#include "CommandInvoker.h"

#include <algorithm>
#include <iostream>
#include <SDL_timer.h>
#include <vector>

#include "Command.h"


CommandInvoker::CommandInvoker(GameObject* owner) :
	Component("CommandInvoker", owner),
	commandCopy(nullptr)
{
}

void CommandInvoker::ExecuteCommand(Command* command)
{
	command->Execute();

	if (command->GetType() == CommandType::SwapCommand && !commandStack.empty()) {
		std::unique_ptr<Command> lastCommand = std::move(commandStack.top());
		commandStack.pop();
		lastCommand->SetUndoSteps(3);
		commandStack.push(std::unique_ptr<Command>(command));
		commandStack.push(std::move(lastCommand));
		std::cout << "Rearrange order!\n";
	}
	else {
		commandStack.push(std::unique_ptr<Command>(command));
	}
}

void CommandInvoker::Undo()
{
	if (commandStack.empty()) {
		std::cout << "No commands to undo.\n";
		return;
	}

	std::vector<std::unique_ptr<Command>> tempCommands;

	const int stepsToUndo = commandStack.top()->GetUndoSteps();
	for (int i = 0; i < stepsToUndo && !commandStack.empty(); ++i) {
		tempCommands.push_back(std::move(commandStack.top()));
		commandStack.pop();
	}

	for (std::vector<std::unique_ptr<Command>>::reverse_iterator it = tempCommands.rbegin(); it != tempCommands.rend(); ++it) {
		std::cout << "Undo: " << (*it)->ToString() << "\n";
		(*it)->Undo();
	}
}

void CommandInvoker::ScheduleUndoAll(Uint32 intervalMs)
{
	isUndoAllScheduled = true;
	undoAllIntervalMs = intervalMs;
	lastUndoTime = SDL_GetTicks() - undoAllIntervalMs;
}

void CommandInvoker::CancelUndoAll()
{
	isUndoAllScheduled = false;
}

void CommandInvoker::Update()
{
	if (isUndoAllScheduled && !commandStack.empty()) {
		const Uint32 currentTime = SDL_GetTicks();
		if (currentTime - lastUndoTime >= undoAllIntervalMs) {
			lastUndoTime = currentTime;
			Undo();

			if (commandStack.empty()) {
				isUndoAllScheduled = false;
			}
		}
	}
}

void CommandInvoker::DebugCommandStack()
{
	std::stack<std::unique_ptr<Command>> tempStack;
	const std::string indent(6, ' ');

	std::cout << "Current Command Stack:" << "\n";
	while (!commandStack.empty()) {

		std::cout << indent << commandStack.top()->ToString() << "\n";

		tempStack.push(std::move(commandStack.top()));
		commandStack.pop();
	}

	while (!tempStack.empty()) {
		commandStack.push(std::move(tempStack.top()));
		tempStack.pop();
	}

	if (commandStack.empty())
		std::cout << "\n" << indent << "Command Stack is empty!";

	std::cout << "\n";
}

void CommandInvoker::PreProcessUndoStack() {
	if (commandStack.size() < 2) return;
	std::cout << "\n\n\n\n\nPreProcessUndoStack\n\n\n\n\n";
	std::vector<std::unique_ptr<Command>> tempCommands;
	while (!commandStack.empty()) {
		tempCommands.push_back(std::move(commandStack.top()));
		commandStack.pop();
	}

	if (tempCommands[tempCommands.size() - 1]->GetType() == CommandType::SwapCommand)
	{
		std::swap(tempCommands[tempCommands.size() - 1], tempCommands[tempCommands.size() - 2]);
	}

	for (std::vector<std::unique_ptr<Command>>::reverse_iterator it = tempCommands.rbegin(); it != tempCommands.rend(); ++it) {
		commandStack.push(std::move(*it));
	}
}
