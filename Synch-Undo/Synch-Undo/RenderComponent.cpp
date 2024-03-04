#include "RenderComponent.h"
#include "Character.h"
#include "GameObject.h"

RenderComponent::RenderComponent(GameObject* owner, const std::function<void(SDL_Renderer*, const TransformComponent*, const SDL_Color color)>& customRender, const SDL_Color color)
	: Component("RenderComponent", owner),
	color(color),
	isVisible(true),
	transformComponent(nullptr),
	customRender(customRender)
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Render(SDL_Renderer* renderer, const TransformComponent* transformComponent, const SDL_Color color) const
{
	if (!isVisible) return;

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
		const Character* character = owner->GetComponent<Character>();
		if (character)
			DrawArrow(renderer, transformComponent, static_cast<int>(character->GetFacingDirection()));
	}
}

void RenderComponent::DrawArrow(SDL_Renderer* renderer, const TransformComponent* transformComponent,
	const int direction)
{
	const SDL_Rect rect = {
		transformComponent->GetX(),
		transformComponent->GetY(),
		transformComponent->GetWidth(),
		transformComponent->GetHeight()
	};

	const int centerX = rect.x + rect.w / 2;
	const int centerY = rect.y + rect.h / 2;

	SDL_Point points[4];
	switch (direction) {
	case 0:
		points[0] = { centerX, rect.y };
		points[1] = { centerX - 5, centerY };
		points[2] = { centerX + 5, centerY };
		break;
	case 1:
		points[0] = { centerX, rect.y + rect.h };
		points[1] = { centerX - 5, centerY };
		points[2] = { centerX + 5, centerY };
		break;
	case 2:
		points[0] = { rect.x + rect.w, centerY };
		points[1] = { centerX, centerY - 5 };
		points[2] = { centerX, centerY + 5 };
		break;
	case 3:
		points[0] = { rect.x, centerY };
		points[1] = { centerX, centerY - 5 };
		points[2] = { centerX, centerY + 5 };
		break;
	}
	points[3] = points[0];

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, points, 4);
}
