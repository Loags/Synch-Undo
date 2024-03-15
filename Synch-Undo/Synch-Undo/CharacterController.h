#pragma once
#include <SDL_events.h>

#include "CommandInvoker.h"

class GameStateManager;
class Character;

class CharacterController
{
private:
	CommandInvoker* commandInvoker;

protected:
	SDL_KeyCode undoKey;
	Character* character;
	GameStateManager* gameStateManager;

public:
	CharacterController();
	void SetCharacter(Character* character);
	virtual ~CharacterController() = default;

	void HandleInput(const SDL_Event& event) const;
	void HandleUndo() const;
};

