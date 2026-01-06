#pragma once
class Spawner;

class Enemy
{
  public:
	Enemy(Spawner* Owner);
	void TakeDamage(int Amount);

  private:
	void Die();
	Spawner* MySpawner;
	int Health{100};
};