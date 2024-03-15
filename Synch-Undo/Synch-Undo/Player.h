#pragma once
#include "Character.h"
#include "Movable.h"

class GameObject;

class Player : public Character
{
private:
	int score;

public:
	Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int playerSize);
	~Player() override = default;
	void Update() override;
	void Move(const GameObject* gridObject, const Direction newFacingDirection) override;
	void Die() override;
	void Respawn() override;
	int GetScore() const { return score; }
	void SetScore(const int amount) { score += amount; }
};
