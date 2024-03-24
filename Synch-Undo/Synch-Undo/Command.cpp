#include "Command.h"

Command::Command(GameObject* object) :
	undoSteps(1),
	object(object)
{
}
