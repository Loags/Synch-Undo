#include "CharacterController.h"
#include "Character.h"
#include "MoveCommand.h"

CharacterController::CharacterController() :
	undoKey(SDLK_u),
	character(nullptr),
	commandInvoker(nullptr)
{
}

void CharacterController::SetCharacter(Character* character)
{
	this->character = character;
	commandInvoker = character->GetCommandInvoker();
}

void CharacterController::HandleInput(const SDL_Event& event) const {
	if (character == nullptr) return;

	if (event.key.repeat != 0)
	{
		return;
	}

	if (event.key.keysym.sym == undoKey)
	{
		HandleUndo();

		return;
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	const bool isShiftPressed = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];

	const std::unordered_map<SDL_Keycode, Movable::Direction>& keyMap = character->GetKeyMap();
	const SDL_Keycode attackKey = character->GetAttackKey();


	if (event.key.keysym.sym == attackKey)
	{
		character->Attack();
		return;
	}

	const std::unordered_map<SDL_Keycode, Movable::Direction>::const_iterator it = keyMap.find(event.key.keysym.sym);
	if (it != keyMap.end())
	{
		if (isShiftPressed)
		{
			character->Rotate(it->second);
		}
		else
		{
			character->Move(character->GetGridObject(), it->second);
		}
	}

}

void CharacterController::HandleUndo() const
{
	commandInvoker->Undo();
}
