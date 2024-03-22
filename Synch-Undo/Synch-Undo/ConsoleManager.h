#pragma once
#include "Component.h"
#include "Movable.h"

class ConsoleManager : public Component
{
private:
	bool consoleAccess = false;
	const std::string indent;

	static std::string DirectionToString(Movable::Direction direction) {
		switch (direction) {
		case Movable::Direction::North: return "North";
		case Movable::Direction::South: return "South";
		case Movable::Direction::West: return "West";
		case Movable::Direction::East: return "East";
		}
	}
public:
	ConsoleManager(GameObject* owner);

	void Update() override;
	void ProcessInput();
	void SetConsoleAccess(bool access) { consoleAccess = access; }
	bool GetConsoleAccess() const { return consoleAccess; }

private:
	void ShowControls() const;
	void ShowStats() const;
	void ShowScorePickups() const;
	void ShowHealthPickUps() const;
	void ShowItems() const;
	void ShowCommandStack() const;
};

