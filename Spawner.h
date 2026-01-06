#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

struct DifficultyLevel {
	Uint32 SpawnInterval;
	int EnemyHealth;
	float EnemySpeed;
};

class Spawner
{
  public:
	Spawner()
	{
		Difficulty = {
			{2000, 100, 1.0f}, {1500, 120, 1.2f}, {1000, 150, 1.5f},
			{800, 200, 1.8f},  {500, 250, 2.0f},
		};
	}

	static Uint32 DifficultyCallback(void* SpawnerPtr, SDL_TimerID timerID,
									 Uint32 interval)
	{
		auto* Spawner = static_cast<class Spawner*>(SpawnerPtr);
		Spawner->IncreaseDifficulty();
		return interval;
	}

	void HandleEvent(SDL_Event& E)
	{
		if (E.type == SDL_EVENT_KEY_DOWN) {
			if (E.key.key = SDLK_SPACE) {
				Start();
			}
		}
	}

	void Start()
	{
		UpdateSpawnTimer();

		DifficultyTimer = SDL_AddTimer(30000, DifficultyCallback, this);
	}

	void IncreaseDifficulty()
	{
		if (CurrentLevel < Difficulty.size() - 1) {
			CurrentLevel++;
			std::cout << "Difficulty increased to level " << CurrentLevel + 1
					  << "!\n";

			UpdateSpawnTimer();
		}
	}

  private:
	void UpdateSpawnTimer()
	{
		if (SpawnTimer) {
			SDL_RemoveTimer(SpawnTimer);
		}

		auto& Level = Difficulty[CurrentLevel];
		SpawnTimer = SDL_AddTimer(Level.SpawnInterval, SpawnEnemy, this);
	}

	static Uint32 SpawnEnemy(void* SpawnerPtr, SDL_TimerID timerID,
							 Uint32 interval)
	{
		auto* Spawner{static_cast<class Spawner*>(SpawnerPtr)};

		auto& Level{Spawner->Difficulty[Spawner->CurrentLevel]};

		std::cout << "Spawning enemy with:\n"
				  << " Health: " << Level.EnemyHealth << "\n"
				  << " Speed:  " << Level.EnemySpeed << "\n";

		return interval;
	}

	std::vector<DifficultyLevel> Difficulty;
	size_t CurrentLevel{0};
	SDL_TimerID SpawnTimer{0};
	SDL_TimerID DifficultyTimer{0};
};