#pragma once
#include <SDL_events.h>

#include "CommandInvoker.h"

class Character;

class CharacterController
{
protected:
	SDL_KeyCode undoKey;
	Character* character;
	CommandInvoker* commandInvoker;

public:
	CharacterController();
	void SetCharacter(Character* character);
	virtual ~CharacterController() = default;

	void HandleInput(const SDL_Event& event) const;
	void HandleUndo() const;
};

