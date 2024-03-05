#include "CharacterController.h"

#include "AttackCommand.h"
#include "Character.h"
#include "MoveCommand.h"
#include "RotateCommand.h"

CharacterController::CharacterController() :
	character(nullptr),
	undoKey(SDLK_u)
{
}

void CharacterController::SetCharacter(Character* character)
{
	this->character = character;
	rootObject = character->GetOwner()->GetRootObject();
	commandInvoker = rootObject->GetComponent<CommandInvoker>();
}

void CharacterController::HandleInput(const SDL_Event& event) const {
	if (character == nullptr) return;
	if (event.key.keysym.sym == undoKey)
	{
		HandleUndo();
		return;
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	const bool isShiftPressed = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];

	const std::unordered_map<SDL_Keycode, Movable::Direction>& keyMap = character->GetKeyMap();
	const SDL_Keycode attackKey = character->GetAttackKey();


	if (event.key.keysym.sym == attackKey) {
		AttackCommand* attackCommand = new AttackCommand(character);
		commandInvoker->ExecuteCommand(attackCommand);
		return;
	}

	const std::unordered_map<SDL_Keycode, Movable::Direction>::const_iterator it = keyMap.find(event.key.keysym.sym);
	if (it != keyMap.end()) {
		if (isShiftPressed) {
			RotateCommand* rotateCommand = new RotateCommand(character, it->second);
			commandInvoker->ExecuteCommand(rotateCommand);
		}
		else {
			MoveCommand* moveCommand = new MoveCommand(character, it->second);
			commandInvoker->ExecuteCommand(moveCommand);
		}
	}
}

void CharacterController::HandleUndo() const
{
	commandInvoker->Undo();
}
