#pragma once
#include <string>

class GameObject;

class Command
{
protected:
	enum class CommandType { Single, Double };
	GameObject* object;
	CommandType type;

public:
	virtual ~Command() = default;
	Command(GameObject* object);
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual std::string ToString() const = 0;
	void SetCommandType(CommandType newType) { type = newType; }
};

