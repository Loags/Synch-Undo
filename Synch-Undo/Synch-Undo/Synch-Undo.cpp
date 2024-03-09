#include <iostream>

#include "CommandInvoker.h"
#include "Enemy.h"
#include "SDL.h"
#include "Grid.h"
#include "ItemManager.h"
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
		cout << "SDL initialization succeeded!\n";
	}

	// Create the SDL window and renderer
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	GameObject* rootObject = new GameObject(nullptr, "Root");
	CommandInvoker* commandInvoker = new CommandInvoker(rootObject);
	rootObject->AddComponent(commandInvoker);


	// Create the gridRef GameObject and add its component
	GameObject* gridObject = new GameObject(rootObject, "Grid");
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	Grid* grid = new Grid(gridObject, windowWidth, windowHeight, CELL_SIZE);
	gridObject->AddComponent(grid);

	GameObject* playerObject = new GameObject(rootObject, "Player");
	Player* player = new Player(playerObject, gridObject, CELL_SIZE, CELL_SIZE, CELL_SIZE / 8, CELL_SIZE * 0.75);
	playerObject->AddComponent(player);

	GameObject* enemyObject = new GameObject(rootObject, "Enemy");
	Enemy* enemy = new Enemy(enemyObject, gridObject, CELL_SIZE * 4, CELL_SIZE * 1, CELL_SIZE / 8, CELL_SIZE * 0.75);
	enemyObject->AddComponent(enemy);


	rootObject->AddChildGameObject(gridObject);
	rootObject->AddChildGameObject(playerObject);
	rootObject->AddChildGameObject(enemyObject);

	ItemManager* itemManager = new ItemManager(rootObject);
	rootObject->AddComponent(itemManager);

	//std::cout << "\n";
	//rootObject->PrintComponentsAndChildren();

	// Main game loop setup
	bool gameRunning = true;
	bool consoleAccess = false;
	SDL_Event e;
	while (gameRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
			}
			if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_p)
				{
					consoleAccess = true;
				}
				else if (!consoleAccess)
				{
					if (!player->stats.GetIsDead()) {
						player->HandleInput(e);
					}
					if (!enemy->stats.GetIsDead()) {
						enemy->HandleInput(e);
					}
				}
			}
		}

		while (consoleAccess) {
			std::string input;
			std::cout << "Enter command (type 'print' to display GameObjects and Components, 'exit' to quit): ";
			std::getline(std::cin, input);

			if (input == "print") {
				rootObject->PrintComponentsAndChildren(0);
			}
			else if (input == "exit") {
				consoleAccess = false;
				break;
			}
			else if (input == "start")
			{
				consoleAccess = false;
				break;
			}
			else {
				std::cout << "Unknown command. Please try again.\n";
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