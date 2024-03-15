#pragma once
#include "Component.h"

class GameStateManager : public Component
{
public:
	enum class TurnState {
		PlayerTurn,
		EnemyTurn
	};

private:
	static TurnState turnState;

public:
	GameStateManager(GameObject* owner);
	static TurnState GetCurrentTurnState() { return turnState; }
	static void SetCurrentTurnState(TurnState newTurnState) { turnState = newTurnState; }
	void Update() override;
};

