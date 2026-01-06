#include "SDL3/SDL_events.h"
#include "Spawner.h"
#include "Window.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

int main(int, char**)
{
	SDL_Init(SDL_INIT_VIDEO);
	Window GameWindow;
	Spawner EnemySpawner;

	SDL_Event Event;
	bool isRunning{true};

	while (isRunning) {
		while (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			} else {
				EnemySpawner.HandleEvent(Event);
			}
		}
		GameWindow.Render();
		GameWindow.Update();
	}
	SDL_Quit();
	return 0;
}