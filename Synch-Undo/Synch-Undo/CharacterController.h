#pragma once
#include <SDL_events.h>

#include "CommandInvoker.h"

class GameStateManager;
class Character;

class CharacterController
{
protected:
	SDL_KeyCode undoKey;
	Character* character;
	CommandInvoker* commandInvoker;
	GameStateManager* gameStateManager;

public:
	CharacterController();
	void SetCharacter(Character* character);
	virtual ~CharacterController() = default;

	void HandleInput(const SDL_Event& event) const;
	void HandleUndo() const;
};

