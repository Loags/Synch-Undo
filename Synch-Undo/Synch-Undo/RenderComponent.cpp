#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* owner, const std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)>& customRender, const SDL_Color color)
	: Component(owner),
	color(color),
	customRender(customRender)
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Render(SDL_Renderer* renderer, const TransformComponent* transformComponent, const SDL_Color color) const
{
	if (customRender)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		customRender(renderer, transformComponent, color);
	}
	else
	{
		const SDL_Rect rect = {
		transformComponent->GetX(),
		transformComponent->GetY(),
		transformComponent->GetWidth(),
		transformComponent->GetHeight()
		};

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}
