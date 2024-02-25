#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(GameObject* owner, const int x, const int y)
	: Component(owner), x(x), y(y) {}

void PlayerComponent::Update() {
	// Update logic for the player
}

void PlayerComponent::Render(SDL_Renderer* renderer) {
	// rendering code for the player
}
