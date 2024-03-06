#pragma once
#include <memory>
#include <SDL_stdinc.h>
#include <stack>
#include "Component.h"

class Command;

class CommandInvoker : public Component
{
private:
	std::stack<std::unique_ptr<Command>> commandStack;
	int counterUndo = 0;
	int counterUndoAll = 0;
	bool isUndoAllScheduled = false;
	Uint32 undoAllIntervalMs = 1000;
	Uint32 lastUndoTime = 0;


public:
	CommandInvoker(GameObject* owner);

	void ExecuteCommand(Command* command);
	void Undo();
	void ScheduleUndoAll(Uint32 intervalMs);
	void CancelUndoAll();
	void Update() override;
	void DebugCommandStack();
	bool GetIsUndoAllScheduled()const { return isUndoAllScheduled; }
};

