#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(const std::shared_ptr<GameObject>& owner, const int x, const int y)
	: Component(owner), x(x), y(y) {}

void PlayerComponent::Update() {
	// Update logic for the player
}

void PlayerComponent::Render(SDL_Renderer* renderer) {
	// rendering code for the player
}
