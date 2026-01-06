#define SDL_MAIN_USER_CALLBACKS 1
#include "Window.h"
#include "World.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct GameState {
	Window GameWindow;
	World GameWorld;
	bool ISRunning{true};
	Uint64 PreviousFrame{0};
};

SDL_AppResult AppInit(void** AppState, int, char**)
{
	SDL_Init(SDL_INIT_VIDEO);

	GameState* State{new GameState()};
	State->GameWorld.SpawnGoblin("Goblin Rogue", 100, 200);
	State->PreviousFrame = SDL_GetTicks();
	*AppState = State;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* AppState, SDL_Event* E)
{
	GameState* State{static_cast<GameState*>(AppState)};

	if (E->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	} else {
		State->GameWorld.HandleEvent(*E);
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* AppState)
{
	GameState* State{static_cast<GameState*>(AppState)};

	Uint64 ThisFrame{SDL_GetTicks()};
	Uint64 TimeDelta{ThisFrame - State->PreviousFrame};
	State->PreviousFrame = ThisFrame;
	State->GameWorld.Tick(TimeDelta / 1000.0f);

	State->GameWindow.Render();
	State->GameWorld.Render(State->GameWindow.GetSurface());
	State->GameWindow.Update();

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* AppState, SDL_AppResult Result) { delete AppState; }
