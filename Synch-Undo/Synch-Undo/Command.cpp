#include "Command.h"

Command::Command(GameObject* object)
	: object(object),
	type(CommandType::Single)
{
}
