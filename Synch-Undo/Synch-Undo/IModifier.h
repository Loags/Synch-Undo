#pragma once
class IModifier
{
public:
	virtual void AddValue(int& value) const = 0;
};

