#pragma once
#include <functional>
#include <SDL_render.h>
#include "Component.h"
#include "TransformComponent.h"

class RenderComponent : public Component
{
protected:
	SDL_Color color;
	bool isVisible;
	const TransformComponent* transformComponent;

public:
	std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)> customRender;

	RenderComponent(GameObject* owner, const std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)>& customRender, const SDL_Color color);

	void Update() override;
	void Render(SDL_Renderer* renderer, const TransformComponent* transformComponent, const SDL_Color color) const;
	void SetRenderColor(const SDL_Color newColor) { color = newColor; }
	void SetVisible(bool visible) { isVisible = visible; }
	bool GetVisible() const { return isVisible; }
	SDL_Color GetRenderColor() const { return color; }

	static void DrawArrow(SDL_Renderer* renderer, const TransformComponent* transformComponent, const int direction);
};

