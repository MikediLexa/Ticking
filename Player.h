#pragma once
#include <functional>

class Player
{
  public:
	void TakeDamage(int Damage)
	{
		Health -= Damage;
		if (DefeatCallback && Health <= 0) {
			DefeatCallback();
		}
	}

	int Health;
	std::function<void()> DefeatCallback{nullptr};
};