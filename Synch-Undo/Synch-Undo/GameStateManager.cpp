#include "GameStateManager.h"

GameStateManager::GameStateManager(GameObject* owner) :
	Component("GameStateManager", owner)
{
}

void GameStateManager::Update()
{
}

GameStateManager::TurnState GameStateManager::turnState = TurnState::PlayerTurn;