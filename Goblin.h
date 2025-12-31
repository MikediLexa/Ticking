#pragma once
#include "GameObject.h"

#include <iostream>
#include <string>

class Goblin : public GameObject
{
  public:
	Goblin(const std::string& name, int x, int y)
		: Name(name), xPosition(x), yPosition(y)
	{
	}

	std::string Name;
	int xPosition;
	int yPosition;
	int Velocity{1};

	void HandleEvent(const SDL_Event& E) override
	{
		if (E.type != SDL_EVENT_KEY_DOWN) return;
		if (E.key.key == SDLK_RIGHT) {
			std::cout << "\nHandleEvent() setting velocity to 1";
			Velocity = 1;
		} else if (E.key.key == SDLK_LEFT) {
			std::cout << "\nHandleEvent() setting velocity to -1";
			Velocity = -1;
		}
	}

	void Tick() override
	{
		std::cout << "\nTick() updating position";
		xPosition += Velocity;
	}

	void Render(SDL_Surface* Surface) override
	{
		std::cout << " - Rendering at x = " << xPosition;
	}
};