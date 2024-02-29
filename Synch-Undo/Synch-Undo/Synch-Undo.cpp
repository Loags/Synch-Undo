#include <iostream>

#include "Enemy.h"
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
	Player* player = new Player(playerObject, gridObject, CELL_SIZE, CELL_SIZE, CELL_SIZE / 8, CELL_SIZE * 0.75);
	playerObject->AddComponent(player);

	GameObject* enemyObject = new GameObject("Enemy");
	Enemy* enemy = new Enemy(enemyObject, gridObject, CELL_SIZE * 4, CELL_SIZE * 1, CELL_SIZE / 8, CELL_SIZE * 0.75);
	enemyObject->AddComponent(enemy);


	rootObject->AddChildGameObject(gridObject);
	rootObject->AddChildGameObject(playerObject);
	rootObject->AddChildGameObject(enemyObject);

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

				case SDLK_w:
					player->Move(gridObject, Movable::Direction::North);
					break;
				case SDLK_s:
					player->Move(gridObject, Movable::Direction::South);
					break;
				case SDLK_a:
					player->Move(gridObject, Movable::Direction::West);
					break;
				case SDLK_d:
					player->Move(gridObject, Movable::Direction::East);
					break;
				case SDLK_SPACE:
					player->Attack();
					break;


				case SDLK_UP:
					enemy->Move(gridObject, Movable::Direction::North);
					break;
				case SDLK_DOWN:
					enemy->Move(gridObject, Movable::Direction::South);
					break;
				case SDLK_LEFT:
					enemy->Move(gridObject, Movable::Direction::West);
					break;
				case SDLK_RIGHT:
					enemy->Move(gridObject, Movable::Direction::East);
					break;
				case SDLK_m:
					enemy->Attack();
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