#pragma once
#include <SDL_events.h>

class Character;

class CharacterController
{
protected:
	Character* character;
public:
	CharacterController();
	virtual ~CharacterController() = default;

	void SetCharacter(Character* character) { this->character = character; }
	void HandleInput(const SDL_Event& event) const;
};

