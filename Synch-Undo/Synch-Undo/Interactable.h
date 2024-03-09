#pragma once
class Interactable
{
protected:
	~Interactable() = default;

public:
	virtual void Interact() = 0;
};

