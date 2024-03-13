#pragma once
#include <string>

class GameObject;

class Command
{
public:
	enum class CommandType { Single, Double };

protected:
	GameObject* object;
	CommandType type;

public:
	virtual ~Command() = default;
	Command(GameObject* object);
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual std::string ToString() const = 0;
	virtual Command* Clone() const = 0;
	void SetCommandType(CommandType newType) { type = newType; }
	CommandType GetCommandType() const { return type; }
};

