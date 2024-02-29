#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* owner, const int posX, const int posY, const int width, const int height) :
	Component(owner),
	posX(posX),
	posY(posY),
	width(width),
	height(height)
{}

void TransformComponent::Update()
{}
