#pragma once
#include <functional>
#include <SDL_render.h>
#include "Component.h"
#include "TransformComponent.h"

class RenderComponent : public Component
{
protected:
	SDL_Color color;
	const TransformComponent* transformComponent;

public:
	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> customRender;

	RenderComponent(GameObject* owner, const std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)>& customRender, const SDL_Color color);

#pragma region Component

	void Update() override;
	std::string GetName() const override { return "RenderComponent"; }

#pragma endregion Component

	void Render(SDL_Renderer* renderer, const TransformComponent* transformComponent, const SDL_Color color)const;
	void SetRenderColor(const SDL_Color newColor) { color = newColor; }
	SDL_Color GetRenderColor() const { return color; }
};

