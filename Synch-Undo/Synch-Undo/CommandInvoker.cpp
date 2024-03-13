#include "CommandInvoker.h"

#include <iostream>
#include <SDL_timer.h>

#include "Command.h"


CommandInvoker::CommandInvoker(GameObject* owner) :
	Component("CommandInvoker", owner),
	commandCopy(nullptr)
{
}

void CommandInvoker::ExecuteCommand(Command* command)
{
	command->Execute();
	commandStack.push(std::unique_ptr<Command>(command));
}

void CommandInvoker::Undo()
{
	if (!commandStack.empty()) {
		counterUndo += 1;
		if (counterUndo % 2 == 0) return;

		const std::unique_ptr<Command>& command = commandStack.top();
		if (command->GetCommandType() == Command::CommandType::Double && commandCopy == nullptr) {
			commandCopy = command->Clone();
			commandStack.pop();

			if (!commandStack.empty()) {
				const std::unique_ptr<Command>& nextCommand = commandStack.top();
				nextCommand->Undo();
				commandStack.pop();
			}
			commandCopy->Undo();
			delete commandCopy;
			commandCopy = nullptr;
		}
		else {
			command->Undo();
			commandStack.pop();
		}
	}
}

void CommandInvoker::ScheduleUndoAll(Uint32 intervalMs)
{
	counterUndoAll += 1;
	if (counterUndoAll % 2 == 0) return;
	isUndoAllScheduled = true;
	undoAllIntervalMs = intervalMs;
	lastUndoTime = SDL_GetTicks() - undoAllIntervalMs;
}

void CommandInvoker::CancelUndoAll()
{
	if (counterUndoAll % 2 != 0) return;
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

	std::cout << "\n";
}