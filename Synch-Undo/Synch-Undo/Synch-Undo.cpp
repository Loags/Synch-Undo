#include <iostream>

#include "CommandInvoker.h"
#include "ConsoleManager.h"
#include "Enemy.h"
#include "GameStateManager.h"
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

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	GameObject* rootObject = new GameObject(nullptr, "Root");
	CommandInvoker* commandInvoker = new CommandInvoker(rootObject);
	ConsoleManager* consoleManager = new ConsoleManager(rootObject);
	GameStateManager* gameStateManager = new GameStateManager(rootObject);
	rootObject->AddComponent(commandInvoker);
	rootObject->AddComponent(consoleManager);
	rootObject->AddComponent(gameStateManager);

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

	bool gameRunning = true;

	SDL_Event e;
	while (gameRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
			}
			if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_p)
				{
					consoleManager->SetConsoleAccess(true);
				}
				else if (!consoleManager->GetConsoleAccess())
				{
					if (GameStateManager::GetCurrentTurnState() == GameStateManager::TurnState::PlayerTurn && !player->GetIsDead()) {
						player->HandleInput(e);
					}

					const Uint8* state = SDL_GetKeyboardState(nullptr);
					const bool isShiftPressed = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];

					if (e.key.keysym.sym == SDLK_u)
					{
						if (isShiftPressed)
						{
							commandInvoker->GetIsUndoAllScheduled() ? commandInvoker->CancelUndoAll() : commandInvoker->ScheduleUndoAll(100);
						}
						else if (!commandInvoker->GetIsUndoAllScheduled())
							commandInvoker->Undo();
					}
				}
			}
		}

		while (consoleManager->GetConsoleAccess()) {
			consoleManager->ProcessInput();
		}

		rootObject->Update();

		SDL_RenderClear(renderer);
		rootObject->Render(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}