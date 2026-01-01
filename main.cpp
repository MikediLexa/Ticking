#include "Goblin.h"
#include "SDL3/SDL_timer.h"
#include "Window.h"
#include "World.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

int main(int, char**)
{
	SDL_Init(SDL_INIT_VIDEO);
	Window GameWindow;
	World GameWorld;

	Goblin& Enemy{GameWorld.SpawnGoblin("Goblin Rogue", 100, 200)};
	std::cout << "A " << Enemy.Name << " was spawnde in the world\n";

	bool shouldContinue{true};
	SDL_Event Event;
	Uint64 PreviousFrame{0};

	// Game Loop
	while (shouldContinue) {
		Uint64 StartTimer{SDL_GetTicks()};

		// Event Loop - Handle Events Here
		while (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_EVENT_QUIT) {
				shouldContinue = false;
			}
			GameWorld.HandleEvent(Event);
		}

		// Update Objects
		Uint64 ThisFrame{SDL_GetTicks()};
		Uint64 TimeDelta{ThisFrame - PreviousFrame};
		PreviousFrame = ThisFrame;
		GameWorld.Tick(TimeDelta / 1000.0f);

		// Render
		GameWindow.Render();
		GameWorld.Render(GameWindow.GetSurface());
		GameWindow.Update();

		// capping Frame Rate
		Uint64 EndTimer{SDL_GetTicks()};
		Uint64 TimeElapsed{EndTimer - StartTimer};
		if (TimeElapsed < 10) {
			SDL_Delay(10 - Uint32(TimeElapsed));
		}
	}

	SDL_Quit();
	return 0;
}