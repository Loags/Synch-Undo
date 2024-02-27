#include <iostream>
#include "SDL.h"
#include "GameObject.h"
#include "Grid.h"
#include "Player.h"

constexpr int CELL_SIZE = 48;
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
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create the rootObject were all other GameObjects will be children
	GameObject* rootObject = new GameObject("Root");

	// Create the grid GameObject and add its component
	GameObject* gridObject = new GameObject("Grid");
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	Grid* grid = new Grid(gridObject, windowWidth, windowHeight, CELL_SIZE);
	gridObject->AddComponent(grid);

	GameObject* playerObject = new GameObject("Player");
	Player* player = new Player(playerObject, gridObject, CELL_SIZE , CELL_SIZE , CELL_SIZE / 8, CELL_SIZE * 0.75);
	playerObject->AddComponent(player);

	rootObject->AddChildGameObject(gridObject);
	rootObject->AddChildGameObject(playerObject);

	std::cout << "\n";
	rootObject->PrintComponentsAndChildren();

	// Main game loop setup
	bool gameRunning = true;
	SDL_Event e;
	while (gameRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w: // Move up
					player->Move(0, -CELL_SIZE);
					break;
				case SDLK_s: // Move down
					player->Move(0, CELL_SIZE);
					break;
				case SDLK_a: // Move left
					player->Move(-CELL_SIZE, 0);
					break;
				case SDLK_d: // Move right
					player->Move(CELL_SIZE, 0);
					break;
				}
			}
		}

		// Update GameObjects
		rootObject->Update();

		// Render
		SDL_RenderClear(renderer);
		rootObject->Render(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}