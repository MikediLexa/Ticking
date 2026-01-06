
#include "Enemy.h"

#include "Spawner.h"

#include <iostream>

Enemy::Enemy(Spawner* Owner) : MySpawner(Owner) {}

void Enemy::TakeDamage(int Amount)
{
	Health -= Amount;
	if (Health <= 0) {
		Die();
	}
}

void Enemy::Die()
{
	std::cout << "Enemy defeated!\n";
	MySpawner->ScheduleRespawn();
}