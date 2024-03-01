#pragma once
#include <string>
#include <array>

class CharacterStats
{
private:
	int health;
	int initialHealth;
	int attackPower;
	bool isDead;
public:
	enum CharacterType
	{
		Player,
		Enemy
	};
	static const std::array<std::string, 2> CharacterTypeStrings;


	void SetHealth(int newHealth) { health = newHealth; }
	void SetInitialHealth(int newInitialHealth) { initialHealth = newInitialHealth; }
	void SetAttackPower(int newAttackPower) { attackPower = newAttackPower; }
	void SetisDead(bool newDead) { isDead = newDead; }

	int GetHealth() const { return health; }
	int GetInitialHealth() const { return initialHealth; }
	int GetAttackPower() const { return attackPower; }
	bool GetIsDead() const { return isDead; }



	CharacterType type;

	CharacterStats(const int health, const int attackPower, const CharacterType type);
};

