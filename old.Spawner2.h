#pragma once

#include "Enemy.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

const Uint32 ENEMY_SPAWN_EVENT = SDL_RegisterEvents(1);

Uint32 QueueSpawnEvent(void* userdate, SDL_TimerID timerID, Uint32 interval)
{
	SDL_Event SpawnEvent;
	SpawnEvent.type = ENEMY_SPAWN_EVENT;
	SDL_PushEvent(&SpawnEvent);
	return interval;
}

struct SpawnerConfig {
	float IntervalMultiplier;
	Uint32 MinInterval;
};

Uint32 SpawnGoblin(void* ConfigPtr, SDL_TimerID timerID, Uint32 CurrentDelay)
{
	std::cout << "Spawning a Goblin - Spawnrate: " << CurrentDelay << "\n";

	SpawnerConfig* Config{static_cast<SpawnerConfig*>(ConfigPtr)};

	Uint32 nextDelay{
		static_cast<Uint32>(CurrentDelay * Config->IntervalMultiplier)};

	return std::max(nextDelay, Config->MinInterval);
}

class Spawner
{
  public:
	void ScheduleRespawn()
	{
		CurrentEnemy.reset();
		std::cout << "Scheduling respawn in 10s\n";
		Timer = SDL_AddTimer(10000, SpawnCallback, this);
	}

	static Uint32 SpawnCallback(void* SpawnerPtr, SDL_TimerID timerID,
								Uint32 interval)
	{
		auto* Spawner{static_cast<class Spawner*>(SpawnerPtr)};
		Spawner->SpawnEnemy();
		return 0;
	}

	void HandleEvent(const SDL_Event& E)
	{
		if (E.type == ENEMY_SPAWN_EVENT) {
			SpawnEnemy();
		} else if (E.type == SDL_EVENT_KEY_DOWN) {
			HandleKeyDownEvent(E.key);
		}
	}

	void HandleKeyDownEvent(const SDL_KeyboardEvent& E)
	{
		if (E.key == SDLK_SPACE) {
			StartTimer();
		} else if (E.key == SDLK_ESCAPE) {
			if (CurrentEnemy) {
				CurrentEnemy->TakeDamage(100);
			}
		}
	}

	void StartTimer()
	{
		if (Timer) {
			std::cout << "Already spawning - ignoring event\n";
		} else {
			std::cout << "Starting Spawner\n";
			Timer = SDL_AddTimer(1000, SpawnGoblin, &Config);
			isSpawning = true;
		}
		if (!Timer) {
			std::cout << "Error creating timer: " << SDL_GetError();
		}
	}

	void SpawnEnemy()
	{
		CurrentEnemy = std::make_unique<Enemy>(this);
		std::cout << "Enemy spawned!\n";
		Timer = 0;
	}

	void RemoveTimer()
	{
		std::cout << "Removing Timer\n";

		if (SDL_RemoveTimer(Timer)) {
			std::cout << "Timer with ID " << Timer << " Removed Successfully\n";
			Timer = 0;
		} else {
			std::cout << "Timer with ID " << Timer << " was not found\n";
		}
	}

	//	Spawner(const Spawner&) = delete;
	//	Spawner& operator=(const Spawner&) = delete;
	//
	//	~Spawner()
	//	{
	//		if (Timer) {
	//			SDL_RemoveTimer(Timer);
	//		}
	//	}

  private:
	bool isSpawning{false};
	SpawnerConfig Config{0.8f, 600};
	SDL_TimerID Timer{0};
	std::unique_ptr<Enemy> CurrentEnemy;
};