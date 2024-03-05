#pragma once
#include "GameObject.h"


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

public:
	virtual ~Movable() = default;
	Movable(const GameObject* movableOwner, const int offSet);

	virtual bool Move(const GameObject* gridObject, const Direction newFacingDirection);
	Direction GetFacingDirection()const { return facingDirection; }
	void SetFacingDirection(Direction newDirection) { facingDirection = newDirection; }
};

