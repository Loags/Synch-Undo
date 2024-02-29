#pragma once
#include "GameObject.h"


class Movable
{
private:
	const GameObject* movableOwner;
protected:
	int offSet;
public:
	Movable(const GameObject* movableOwner, const int offSet);

	virtual void Move(const GameObject* gridObject, const int deltaX, const int deltaY) const;
};

