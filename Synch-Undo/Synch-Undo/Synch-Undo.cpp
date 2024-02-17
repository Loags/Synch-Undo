#include <iostream>
#include "SDL.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "PlayerComponent.h"

using namespace std;
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
		return 1;
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	// Create the SDL window and renderer
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create the grid GameObject and add its component
	shared_ptr<GameObject> gridObject = make_shared<GameObject>("Grid");
	shared_ptr<GridComponent> gridComponent = make_shared<GridComponent>(gridObject, 10, 10, 32);
	gridObject->AddComponent(gridComponent);

	// Create the player GameObject and add its component
	shared_ptr<GameObject> playerObject = make_shared<GameObject>("Player");
	shared_ptr<PlayerComponent> playerComponent = make_shared<PlayerComponent>(playerObject, 5, 5);
	playerObject->AddComponent(playerComponent);

	// Main game loop setup
	bool gameRunning = true;
	SDL_Event e;
	while (gameRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
			}
		}

		// Update GameObjects
		gridObject->Update();
		playerObject->Update();

		// Render
		SDL_RenderClear(renderer);
		gridComponent->Render(renderer);
		playerComponent->Render(renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}