#pragma once
#include <string>

class GameObject;

enum class CommandType {
	Default,
	SwapCommand
};

class Command
{
private:
	int undoSteps;

protected:
	GameObject* object;

public:
	virtual ~Command() = default;
	Command(GameObject* object);
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual std::string ToString() const = 0;
	virtual Command* Clone() const = 0;
	virtual CommandType GetType() const { return CommandType::Default; }
	void SetUndoSteps(int steps) { undoSteps = steps; }
	int GetUndoSteps() const { return undoSteps; }
};

