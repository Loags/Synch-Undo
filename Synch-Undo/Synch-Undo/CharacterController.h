#pragma once
#include <SDL_events.h>

#include "CommandInvoker.h"

class Character;

class CharacterController
{
protected:
	Character* character;
	SDL_KeyCode undoKey;
	GameObject* rootObject;
	CommandInvoker* commandInvoker;

public:
	CharacterController();
	virtual ~CharacterController() = default;

	void SetCharacter(Character* character);
	void HandleInput(const SDL_Event& event) const;
	void HandleUndo() const;
};

