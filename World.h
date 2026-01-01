#pragma once
#include "GameObject.h"
#include "Goblin.h"

#include <memory>
#include <vector>

class World
{
  public:
	void HandleEvent(const SDL_Event& E)
	{
		for (auto& Object : Objects) {
			Object->HandleEvent(E);
		}
	}

	void Tick(float TimeDelta)
	{
		for (auto& Object : Objects) {
			Object->Tick(TimeDelta);
		}
	}

	void Render(SDL_Surface* Surface)
	{
		for (auto& Object : Objects) {
			Object->Render(Surface);
		}
	}

	Goblin& SpawnGoblin(const std::string& Name, int x, int y)
	{
		Objects.emplace_back(std::make_unique<Goblin>(Name, x, y));
		return static_cast<Goblin&>(*Objects.back());
	}

  private:
	std::vector<std::unique_ptr<GameObject>> Objects;
};