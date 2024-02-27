#pragma once
#include "Component.h"
#include <SDL.h>
#include "Grid.h"
class GameObject;


class Player : public Component {
private:
	const GameObject* gridObject;
	int x;
	int y;
	int offSet;
	SDL_Color colorPlayer;

public:

	Player(GameObject* owner, const GameObject* gridObject, const int posX, const int posY, const int offSet, const int playerSize);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	std::string GetName() const override { return "Player"; }

	void Move(const int deltaX, const int deltaY) const;
};
