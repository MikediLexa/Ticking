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
	Uint64 PreviousFrame{SDL_GetPerformanceCounter()};
	const float PerformanceFrequency{
		static_cast<float>(SDL_GetPerformanceFrequency())};

	// Game Loop
	while (shouldContinue) {

		// Event Loop - Handle Events Here
		while (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_EVENT_QUIT) {
				shouldContinue = false;
			}
			GameWorld.HandleEvent(Event);
		}

		// Update Objects
		Uint64 ThisFrame{SDL_GetPerformanceCounter()};
		float TimeDelta{(ThisFrame - PreviousFrame) / PerformanceFrequency};
		PreviousFrame = ThisFrame;
		std::cout << "\nTimeDelta: " << TimeDelta;

		// Render
		GameWindow.Render();
		GameWorld.Render(GameWindow.GetSurface());
		GameWindow.Update();
	}

	SDL_Quit();
	return 0;
}