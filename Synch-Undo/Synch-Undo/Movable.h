#pragma once
#include "CommandInvoker.h"
#include "GameObject.h"


class Character;

class Movable
{
public:
	enum class Direction { North, South, East, West };
	std::vector<std::string> directionStrings{ "North", "South", "East","West" };
protected:
	int offSet;

private:
	const GameObject* movableOwner;
	Direction facingDirection;
	Character* character;
	CommandInvoker* commandInvoker;

public:
	virtual ~Movable() = default;
	Movable(const GameObject* movableOwner, const int offSet);
	void SetCharacter(Character* character);

	virtual void Move(const GameObject* gridObject, const Direction newFacingDirection);
	Direction GetFacingDirection()const { return facingDirection; }
	void SetFacingDirection(Direction newDirection) { facingDirection = newDirection; }
	void Rotate(const Direction newFacingDirection);
};

