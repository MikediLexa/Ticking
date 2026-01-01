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
	float xPosition;
	float yPosition;
	float Velocity{100.0f};

	void HandleEvent(const SDL_Event& E) override
	{
		if (E.type != SDL_EVENT_KEY_DOWN) return;
		if (E.key.key == SDLK_RIGHT) {
			std::cout << "\nHandleEvent() setting velocity to 1";
			Velocity = 100.0f;
		} else if (E.key.key == SDLK_LEFT) {
			std::cout << "\nHandleEvent() setting velocity to -1";
			Velocity = -100.0f;
		}
	}

	void Tick(float TimeDelta) override
	{
		xPosition += Velocity * TimeDelta;
		std::cout << "Goblin position: " << xPosition << '\n';
	}

	void Render(SDL_Surface* Surface) override
	{
		// ,,,
	}
};