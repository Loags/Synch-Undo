#pragma once
#include <memory>
#include <SDL_stdinc.h>
#include <stack>
#include "Component.h"

class Command;

class CommandInvoker final : public Component
{
private:
	std::stack<std::unique_ptr<Command>> commandStack;
	bool isUndoAllScheduled = false;
	Uint32 undoAllIntervalMs = 1000;
	Uint32 lastUndoTime = 0;
	Command* commandCopy;

public:
	CommandInvoker(GameObject* owner);

	void ExecuteCommand(Command* command);
	void Undo();
	void ScheduleUndoAll(Uint32 intervalMs);
	void CancelUndoAll();
	void Update() override;
	void DebugCommandStack();
	bool GetIsUndoAllScheduled()const { return isUndoAllScheduled; }
	void PreProcessUndoStack();
};

