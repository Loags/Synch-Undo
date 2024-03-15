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
	TurnState turnState = TurnState::PlayerTurn;

public:
	GameStateManager(GameObject* owner);
	TurnState GetCurrentTurnState() const { return turnState; }
	void SetCurrentTurnState(TurnState newTurnState) { turnState = newTurnState; }
	void Update() override;
};

