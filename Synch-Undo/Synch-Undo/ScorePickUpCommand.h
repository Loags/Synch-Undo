#pragma once
#include "PickUpCommand.h"

class ScorePickUp;

class ScorePickUpCommand : public PickUpCommand
{
private:
	ScorePickUp* scorePickUp;

public:
	ScorePickUpCommand(GameObject* object, Player* player);

	void Execute() override;
	void Undo() override;
	std::string ToString() const override;
};

