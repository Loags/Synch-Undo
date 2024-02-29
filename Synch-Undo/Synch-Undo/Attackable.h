#pragma once

class Attackable
{
public:
	virtual ~Attackable() = default;
	virtual void Attack(Attackable* target) = 0;
	virtual void TakeDamage(int damage) = 0;
};

